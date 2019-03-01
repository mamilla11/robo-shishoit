#include "Display.h"

namespace hw {

constexpr uint16_t Display::NUMBERS[10];

Display::Display() {
	_setupGpio();
}

void Display::setNextChar() {
	static uint8_t _current_char_i = 0;

	_deselect(_current_char_i);

	if (++_current_char_i == CHAR_COUNT) {
		_current_char_i = 0;
	}

	switch(_current_char_i) {
		case 0:
			_setNumber(_char_1_value);
			break;
		case 1:
			_setNumber(_char_2_value);
			break;
		case 2:
			_setNumber(_char_3_value);
			break;
		case 3:
			_setNumber(_char_4_value);
			break;
		default:
			break;
	}

	_select(_current_char_i);
}

void Display::setCharValue(uint8_t char_i, uint8_t value, bool dotted) {
	if (value > 9) {
		return;
	}

	switch (char_i) {
	case 0:
		_char_1_value = NUMBERS[value] | (uint16_t)dotted;
		break;
	case 1:
		_char_2_value = NUMBERS[value] | (uint16_t)dotted;
		break;
	case 2:
		_char_3_value = NUMBERS[value] | (uint16_t)dotted;
		break;
	case 3:
		_char_4_value = NUMBERS[value] | (uint16_t)dotted;
		break;
	default:
		break;
	}
}

void Display::_setNumber(uint16_t number) {
	uint16_t value = gpio_port_read(_numberPort);
	value &= ~NUMBER_MASK;
	value |= number;
	gpio_port_write(_numberPort, value);
}

void Display::_select(uint8_t char_i) {
	switch(char_i) {
		case 0:
			gpio_clear(config::CHAR_1_SEL_PORT, config::CHAR_1_SEL_PIN);
			break;
		case 1:
			gpio_clear(config::CHAR_2_SEL_PORT, config::CHAR_2_SEL_PIN);
			break;
		case 2:
			gpio_clear(config::CHAR_3_SEL_PORT, config::CHAR_3_SEL_PIN);
			break;
		case 3:
			gpio_clear(config::CHAR_4_SEL_PORT, config::CHAR_4_SEL_PIN);
			break;
		default:
			break;
	}
}

void Display::_deselect(uint8_t char_i) {
	switch(char_i) {
		case 0:
			gpio_set(config::CHAR_1_SEL_PORT, config::CHAR_1_SEL_PIN);
			break;
		case 1:
			gpio_set(config::CHAR_2_SEL_PORT, config::CHAR_2_SEL_PIN);
			break;
		case 2:
			gpio_set(config::CHAR_3_SEL_PORT, config::CHAR_3_SEL_PIN);
			break;
		case 3:
			gpio_set(config::CHAR_4_SEL_PORT, config::CHAR_4_SEL_PIN);
			break;
		default:
			break;
	}
}

void Display::_deselectAll() {
	gpio_set(config::CHAR_1_SEL_PORT, config::CHAR_1_SEL_PIN);
	gpio_set(config::CHAR_2_SEL_PORT, config::CHAR_2_SEL_PIN);
	gpio_set(config::CHAR_3_SEL_PORT, config::CHAR_3_SEL_PIN);
	gpio_set(config::CHAR_4_SEL_PORT, config::CHAR_4_SEL_PIN);
}

void Display::_setupGpio() {

	gpio_set_mode(config::CHAR_1_SEL_PORT, GPIO_MODE_OUTPUT_10_MHZ,
					GPIO_CNF_OUTPUT_PUSHPULL, config::CHAR_1_SEL_PIN);
	gpio_set_mode(config::CHAR_2_SEL_PORT, GPIO_MODE_OUTPUT_10_MHZ,
					GPIO_CNF_OUTPUT_PUSHPULL, config::CHAR_2_SEL_PIN);
	gpio_set_mode(config::CHAR_3_SEL_PORT, GPIO_MODE_OUTPUT_10_MHZ,
					GPIO_CNF_OUTPUT_PUSHPULL, config::CHAR_3_SEL_PIN);
	gpio_set_mode(config::CHAR_4_SEL_PORT, GPIO_MODE_OUTPUT_10_MHZ,
					GPIO_CNF_OUTPUT_PUSHPULL, config::CHAR_4_SEL_PIN);

	gpio_set_mode(config::CHAR_SEG_PORT, GPIO_MODE_OUTPUT_10_MHZ,
					GPIO_CNF_OUTPUT_PUSHPULL, NUMBER_MASK);

	_deselectAll();
}

}
