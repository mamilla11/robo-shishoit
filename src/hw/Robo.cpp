#include "Robo.h"

namespace hw {

Robo::Robo() {
	_setupGpio();
}

void Robo::toggleBacklight() {
	gpio_toggle(config::BACKLIGHT_PORT, config::BACKLIGHT_PIN);
}

void Robo::toggleHandLed() {
	gpio_toggle(config::HANDLED_PORT, config::HANDLED_PIN);
}

bool Robo::isLeftButtonPressed() {
	uint16_t isPressed = gpio_get(config::BUTTON_LEFT_PORT, config::BUTTON_LEFT_PIN);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

bool Robo::isRightButtonPressed() {
	uint16_t isPressed = gpio_get(config::BUTTON_RIGHT_PORT, config::BUTTON_RIGHT_PIN);
	if (isPressed == 0) {
		return true;
	}
	return false;
}

bool Robo::isTouchPressed() {
	uint16_t isPressed = gpio_get(config::TOUCH_PORT, config::TOUCH_PIN);

	if (isPressed == 0) {
		return false;
	}
	return true;
}

void Robo::_setupGpio() {
	gpio_set_mode(config::BACKLIGHT_PORT, GPIO_MODE_OUTPUT_50_MHZ,
			      GPIO_CNF_OUTPUT_PUSHPULL, config::BACKLIGHT_PIN);
	gpio_set(config::BACKLIGHT_PORT, config::BACKLIGHT_PIN);

	gpio_set_mode(config::HANDLED_PORT, GPIO_MODE_OUTPUT_50_MHZ,
			      GPIO_CNF_OUTPUT_PUSHPULL, config::HANDLED_PIN);
	gpio_clear(config::HANDLED_PORT, config::HANDLED_PIN);

	gpio_set_mode(config::BUTTON_LEFT_PORT, GPIO_MODE_INPUT,
				  GPIO_CNF_INPUT_FLOAT, config::BUTTON_LEFT_PIN);

	gpio_set_mode(config::BUTTON_RIGHT_PORT, GPIO_MODE_INPUT,
				  GPIO_CNF_INPUT_FLOAT, config::BUTTON_RIGHT_PIN);

	gpio_set_mode(config::TOUCH_PORT, GPIO_MODE_INPUT,
			      GPIO_CNF_INPUT_FLOAT, config::TOUCH_PIN);
}

}
