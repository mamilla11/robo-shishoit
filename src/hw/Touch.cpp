#include "Touch.h"
#include "tasks/LogicTask.h"

namespace hw {

Touch *touchPointer;

Touch::Touch() {
	touchPointer = this;
	_setup_gpio();
	_setup_exti();
}

void Touch::notifyLogicTask() {
	tasks::LogicTask::MsgType msg;
	msg.token = tasks::msg::LogicEvent::TOUCH_PRESSED;
	tasks::LogicTask::fifo_push_from_isr(&msg);
}

void Touch::_setup_gpio() {
	gpio_set_mode(config::TOUCH_PORT, GPIO_MODE_INPUT,
			GPIO_CNF_INPUT_FLOAT, config::TOUCH_PIN);
}

void Touch::_setup_exti() {
	nvic_set_priority(config::TOUCH_NVIC, 191 + 0x10);
	nvic_enable_irq(config::TOUCH_NVIC);
	exti_select_source(config::TOUCH_PIN, config::TOUCH_PORT);
	exti_set_trigger(config::TOUCH_PIN, EXTI_TRIGGER_RISING);
	exti_enable_request(config::TOUCH_PIN);
}

}

void exti9_5_isr(void)
{
	exti_reset_request(config::TOUCH_PIN);
	hw::touchPointer->notifyLogicTask();
}

