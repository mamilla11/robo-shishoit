#include "Buttons.h"
#include <tasks/LogicTask.h>

namespace hw {

Buttons *buttonsPointer;

static volatile uint8_t leftState = 1;
static volatile uint8_t rightState = 1;

Buttons::Buttons() {
	buttonsPointer = this;

	_setupGpio();
	_setupExti();
	_setupTimer();
}

bool Buttons::isLeftButtonPressed() {
	uint16_t isPressed = gpio_get(config::BUTTON_LEFT_PORT, config::BUTTON_LEFT_PIN);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

bool Buttons::isRightButtonPressed() {
	uint16_t isPressed = gpio_get(config::BUTTON_RIGHT_PORT, config::BUTTON_RIGHT_PIN);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

void Buttons::leftButtonPressedHandler()
{
	if (isLeftButtonPressed()) {
		timer_enable_counter(config::LONG_PRESS_TIM);
	} else {
		timer_set_counter(config::LONG_PRESS_TIM, 0);
		timer_disable_counter(config::LONG_PRESS_TIM);
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
	timer_set_counter(config::LONG_PRESS_TIM, 0);
	timer_disable_counter(config::LONG_PRESS_TIM);

	_notifyLogicTask(hw::Buttons::Notification::LEFT_LONG_PRESS);

	_longPressDetected = true;
}

void Buttons::_setupGpio() {
	gpio_set_mode(config::BUTTON_LEFT_PORT, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, config::BUTTON_LEFT_PIN);

	gpio_set_mode(config::BUTTON_RIGHT_PORT, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, config::BUTTON_RIGHT_PIN);
}

void Buttons::_setupExti() {
	nvic_set_priority(config::BUTTONS_NVIC, 191 + 0x10);
	nvic_enable_irq(config::BUTTONS_NVIC);

	exti_select_source(config::BUTTON_LEFT_PIN, config::BUTTON_LEFT_PORT);
	exti_set_trigger(config::BUTTON_LEFT_EXTI, EXTI_TRIGGER_BOTH);
	exti_enable_request(config::BUTTON_LEFT_EXTI);

	exti_select_source(config::BUTTON_RIGHT_PIN, config::BUTTON_RIGHT_PORT);
	exti_set_trigger(config::BUTTON_RIGHT_EXTI, EXTI_TRIGGER_BOTH);
	exti_enable_request(config::BUTTON_RIGHT_EXTI);
}

void Buttons::_setupTimer() {
	timer_set_mode(config::LONG_PRESS_TIM, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(config::LONG_PRESS_TIM, 0xFFFE);
	timer_set_period(config::LONG_PRESS_TIM, 4500);
	timer_generate_event(config::LONG_PRESS_TIM, TIM_EGR_UG); //update deneration
	TIM_DIER(config::LONG_PRESS_TIM) |= TIM_DIER_UIE;
	timer_set_counter(config::LONG_PRESS_TIM, 0);

	nvic_set_priority(config::LONG_PRESS_NVIC_2, config::LONG_PRESS_NVIC_PRIO);
	nvic_enable_irq(config::LONG_PRESS_NVIC_2);
}

void Buttons::_notifyLogicTask(Notification notification) {
	tasks::LogicTask::MsgType msg;

	switch(notification) {
		case Notification::LEFT_PRESSED:
			msg.token = tasks::msg::LogicEvent::LEFT_BUTTON_PRESSED;
			break;
		case Notification::RIGHT_PRESSED:
			msg.token = tasks::msg::LogicEvent::RIGHT_BUTTON_PRESSED;
			break;
		case Notification::LEFT_LONG_PRESS:
			msg.token = tasks::msg::LogicEvent::LEFT_BUTTON_LONG_PRESS;
			break;
	}

	tasks::LogicTask::fifo_push_from_isr(&msg);
}

}

void exti15_10_isr(void) {
	if (exti_get_flag_status(config::BUTTON_LEFT_EXTI)) {
		exti_reset_request(config::BUTTON_LEFT_EXTI);
		hw::buttonsPointer->leftButtonPressedHandler();
	}

	if (exti_get_flag_status(config::BUTTON_RIGHT_EXTI)) {
		exti_reset_request(config::BUTTON_RIGHT_EXTI);
		hw::buttonsPointer->rightButtonPressedHandler();
	}
}

void tim1_up_isr(void) {
	static bool firstTime = true;

	timer_clear_flag(config::LONG_PRESS_TIM, TIM_SR_UIF);
	if (!firstTime) {
		hw::buttonsPointer->longPressDetectedHandler();
	} else {
		firstTime = false;
	}
}

