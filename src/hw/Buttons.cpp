#include <hw/SystemState.h>
#include "Buttons.h"
#include <tasks/LogicTask.h>

namespace hw {

static volatile uint8_t leftState = 1;
static volatile uint8_t rightState = 1;

Buttons::Buttons()
{
	cfg.leftBtnPort    = config::BUTTON_LEFT_PORT;
	cfg.leftBtnPin     = config::BUTTON_LEFT_PIN;
	cfg.rightBtnPort   = config::BUTTON_RIGHT_PORT;
	cfg.rightBtnPin    = config::BUTTON_RIGHT_PIN;

	_setupGpio();
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

//void Buttons::leftButtonPressedHandler()
//{
//	if (isLeftButtonPressed()) {
//		timer_enable_counter(cfg.timer);
//	} else {
//		timer_set_counter(cfg.timer, 0);
//		timer_disable_counter(cfg.timer);
//		if (!_longPressDetected) {
//			_notifyLogicTask(hw::Buttons::Notification::LEFT_PRESSED);
//		} else {
//			_longPressDetected = false;
//		}
//	}
//}

void Buttons::_setupGpio() {
	gpio_set_mode(cfg.leftBtnPort, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, cfg.leftBtnPin);

	gpio_set_mode(cfg.rightBtnPort, GPIO_MODE_INPUT,
						GPIO_CNF_INPUT_FLOAT, cfg.rightBtnPin);
}

}

