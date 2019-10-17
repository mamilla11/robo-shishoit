#include <hw/SystemState.h>
#include "Buttons.h"
#include <tasks/LogicTask.h>

namespace hw {

Buttons *buttonsPointer;

static volatile uint8_t leftState = 1;
static volatile uint8_t rightState = 1;

Buttons::Buttons()
{
	buttonsPointer = this;

	cfg.timer          = config::LONG_PRESS_TIM;
	cfg.timerPrescaler = config::LONG_PRESS_TIM_PRESCALER;
	cfg.timerPeriod    = config::LONG_PRESS_TIM_PERIOD;
	cfg.timerNvic      = config::LONG_PRESS_NVIC;
	cfg.timerNvicPrio  = config::LONG_PRESS_NVIC_PRIO;
	cfg.leftBtnPort    = config::BUTTON_LEFT_PORT;
	cfg.leftBtnPin     = config::BUTTON_LEFT_PIN;
	cfg.leftBtnExti    = config::BUTTON_LEFT_EXTI;
	cfg.leftBtnNvic    = config::BUTTONS_NVIC;
	cfg.rightBtnPort   = config::BUTTON_RIGHT_PORT;
	cfg.rightBtnPin    = config::BUTTON_RIGHT_PIN;
	cfg.rightBtnExti   = config::BUTTON_RIGHT_EXTI;
	cfg.rightBtnNvic   = config::BUTTONS_NVIC;

	_setupGpio();
	_setupExti();
	_setupTimer();
}

bool Buttons::isLeftButtonPressed() {
	uint16_t isPressed = gpio_get(cfg.leftBtnPort, cfg.leftBtnPin);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

bool Buttons::isRightButtonPressed() {
	uint16_t isPressed = gpio_get(cfg.rightBtnPort, cfg.rightBtnPin);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

void Buttons::leftButtonPressedHandler()
{
	if (isLeftButtonPressed()) {
		timer_enable_counter(cfg.timer);
	} else {
		timer_set_counter(cfg.timer, 0);
		timer_disable_counter(cfg.timer);
		if (!_longPressDetected) {
			_notifyLogicTask(hw::Buttons::Notification::LEFT_PRESSED);
		} else {
			_longPressDetected = false;
		}
	}
}

void Buttons::rightButtonPressedHandler() {
	if (isRightButtonPressed()) {
		_notifyLogicTask(hw::Buttons::Notification::RIGHT_PRESSED);
	}
}

void Buttons::longPressDetectedHandler() {
	timer_set_counter(cfg.timer, 0);
	timer_disable_counter(cfg.timer);

	_notifyLogicTask(hw::Buttons::Notification::LEFT_LONG_PRESS);

	_longPressDetected = true;
}

void Buttons::_setupGpio() {
	gpio_set_mode(cfg.leftBtnPort, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, cfg.leftBtnPin);

	gpio_set_mode(cfg.rightBtnPort, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, cfg.rightBtnPin);
}

void Buttons::_setupExti() {
	nvic_set_priority(cfg.leftBtnNvic, 191 + 0x10);
	nvic_set_priority(cfg.rightBtnNvic, 191 + 0x10);

	nvic_enable_irq(cfg.leftBtnNvic);
	nvic_enable_irq(cfg.rightBtnNvic);

	exti_select_source(cfg.leftBtnPin, cfg.leftBtnPort);
	exti_set_trigger(cfg.leftBtnExti, EXTI_TRIGGER_BOTH);
	exti_enable_request(cfg.leftBtnExti);

	exti_select_source(cfg.rightBtnPin, cfg.rightBtnPort);
	exti_set_trigger(cfg.rightBtnExti, EXTI_TRIGGER_BOTH);
	exti_enable_request(cfg.rightBtnExti);
}

void Buttons::_setupTimer() {
	timer_set_mode(cfg.timer, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(cfg.timer, cfg.timerPrescaler);
	timer_set_period(cfg.timer, cfg.timerPeriod);
	timer_generate_event(cfg.timer, TIM_EGR_UG);
	timer_enable_irq(cfg.timer, TIM_DIER_UIE);
	timer_set_counter(cfg.timer, 0);

	nvic_set_priority(cfg.timerNvic, cfg.timerNvicPrio);
	nvic_enable_irq(cfg.timerNvic);
}

void Buttons::_notifyLogicTask(Notification notification) {
	switch(notification) {
		case Notification::LEFT_PRESSED:
			SystemState::pushEvent(SystemState::Event::LEFT_BUTTON_PRESSED);
			break;
		case Notification::RIGHT_PRESSED:
			SystemState::pushEvent(SystemState::Event::RIGHT_BUTTON_PRESSED);
			break;
		case Notification::LEFT_LONG_PRESS:
			SystemState::pushEvent(SystemState::Event::LEFT_BUTTON_LONG_PRESS);
			break;
	}
}

}

void exti15_10_isr(void) {
	if (exti_get_flag_status(hw::buttonsPointer->cfg.leftBtnExti)) {
		exti_reset_request(hw::buttonsPointer->cfg.leftBtnExti);
		hw::buttonsPointer->leftButtonPressedHandler();
	}

	if (exti_get_flag_status(hw::buttonsPointer->cfg.rightBtnExti)) {
		exti_reset_request(hw::buttonsPointer->cfg.rightBtnExti);
		hw::buttonsPointer->rightButtonPressedHandler();
	}
}

void tim1_up_isr(void) {
	static bool firstTime = true;

	timer_clear_flag(hw::buttonsPointer->cfg.timer, TIM_SR_UIF);
	if (!firstTime) {
		hw::buttonsPointer->longPressDetectedHandler();
	} else {
		firstTime = false;
	}
}

