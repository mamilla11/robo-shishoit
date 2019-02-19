#include "ModeSwitcher.h"
#include "tasks/BlinkerTask.h"

namespace hw {

ModeSwitcher *switcherPointer;

ModeSwitcher::ModeSwitcher() {
	switcherPointer = this;
	_setup_gpio();
	_setup_exti();
}

void ModeSwitcher::toNextState() {
	mode = (Mode)((uint8_t)mode + 1);

	if (mode == Mode::COUNT)
		mode = Mode::IDLE;

	tasks::BlinkerTask::MsgType msg;

	switch(mode) {
	case Mode::IDLE:
		msg.token = tasks::msg::BlinkerEvent::IDLE;
		break;
	case Mode::EYES_SETUP:
		msg.token = tasks::msg::BlinkerEvent::EYES_SETUP;
		break;
	case Mode::TIME_SETUP:
		msg.token = tasks::msg::BlinkerEvent::TIME_SETUP;
		break;
	default: break;
	}

	tasks::BlinkerTask::fifo_push_from_isr(&msg);
}

void ModeSwitcher::_setup_gpio() {
	gpio_set_mode(config::TOUCH_PORT, GPIO_MODE_INPUT,
			GPIO_CNF_INPUT_FLOAT, config::TOUCH_PIN);
}

void ModeSwitcher::_setup_exti() {
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
	hw::switcherPointer->toNextState();
}

