#include "Buttons.h"
#include <tasks/LogicTask.h>

namespace hw {

Buttons *buttonsPointer;

Buttons::Buttons() {
	buttonsPointer = this;
	_setup_gpio();
	_setup_exti();
}

void Buttons::notifyLeftButtonPressed() {
	tasks::LogicTask::MsgType msg;
	msg.token = tasks::msg::LogicEvent::LEFT_BUTTON_PRESSED;
	tasks::LogicTask::fifo_push_from_isr(&msg);
}

void Buttons::notifyRightButtonPressed() {
	tasks::LogicTask::MsgType msg;
	msg.token = tasks::msg::LogicEvent::RIGHT_BUTTON_PRESSED;
	tasks::LogicTask::fifo_push_from_isr(&msg);
}

void Buttons::_setup_gpio() {
	gpio_set_mode(config::BUTTON_LEFT_PORT, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, config::BUTTON_LEFT_PIN);

	gpio_set_mode(config::BUTTON_RIGHT_PORT, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, config::BUTTON_RIGHT_PIN);
}

void Buttons::_setup_exti() {
	nvic_set_priority(config::BUTTONS_NVIC, 191 + 0x10);
	nvic_enable_irq(config::BUTTONS_NVIC);

	exti_select_source(config::BUTTON_LEFT_PIN, config::BUTTON_LEFT_PORT);
	exti_set_trigger(config::BUTTON_LEFT_EXTI, EXTI_TRIGGER_RISING);
	exti_enable_request(config::BUTTON_LEFT_EXTI);

	exti_select_source(config::BUTTON_RIGHT_PIN, config::BUTTON_RIGHT_PORT);
	exti_set_trigger(config::BUTTON_RIGHT_EXTI, EXTI_TRIGGER_RISING);
	exti_enable_request(config::BUTTON_RIGHT_EXTI);
}

}

void exti15_10_isr(void)
{
	if (exti_get_flag_status(config::BUTTON_LEFT_EXTI)) {
		hw::buttonsPointer->notifyLeftButtonPressed();
		exti_reset_request(config::BUTTON_LEFT_EXTI);
	}

	if (exti_get_flag_status(config::BUTTON_RIGHT_EXTI)) {
		hw::buttonsPointer->notifyRightButtonPressed();
		exti_reset_request(config::BUTTON_RIGHT_EXTI);
	}
}

