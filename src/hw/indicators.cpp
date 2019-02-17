#include "indicators.h"

namespace hw {

constexpr uint16_t Indicators::NUMBERS[10];

Indicators::Indicators(const uint32_t *sel_ports,
		               const uint32_t *sel_pins,
					   const uint32_t seg_port) : _seg_port(seg_port) {
	for (uint8_t i = 0; i < SELS_COUNT; i++) {
		_sels[i] = new Gpio(sel_ports[i], sel_pins[i], Gpio::Mode::Output10MHz, Gpio::Type::OutputPushPull);
		_sels[i]->set();
	}

	Gpio(_seg_port, SEG_MASK, Gpio::Mode::Output10MHz, Gpio::Type::OutputPushPull);
}

void Indicators::set_number(uint8_t number) {
	if (number > 9) {
		return;
	}

	_deselect(_current_indicator_index);

	uint16_t value = gpio_port_read(_seg_port);
	value &= ~SEG_MASK;
	value |= NUMBERS[number];
	gpio_port_write(_seg_port, value);

	_select(_current_indicator_index);
}

void Indicators::set_next_indicator() {
	_deselect(_current_indicator_index);

	if (++_current_indicator_index == SELS_COUNT) {
		_current_indicator_index = 0;
	}

	_select(_current_indicator_index);
}

void Indicators::_select(uint8_t indicator_index) {
	_sels[indicator_index]->clear();
}

void Indicators::_deselect(uint8_t indicator_index) {
	_sels[indicator_index]->set();
}
}
