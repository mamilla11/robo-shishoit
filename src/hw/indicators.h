#pragma once

#include "stdint.h"
#include <hw/gpio.h>

namespace hw {
class Indicators {
public:
	Indicators(const uint32_t *sel_ports,
			   const uint32_t *sel_pins,
			   const uint32_t seg_port);

	~Indicators() = default;
	void set_number(uint8_t number);
	void set_next_indicator();

private:
	static constexpr uint8_t SELS_COUNT = 4;
	static constexpr uint16_t SEG_MASK = 0x00FF;
	static constexpr uint16_t NUMBERS[10] = {
			0b10111110,
			0b00001010,
			0b11100110,
			0b01101110,
			0b01011010,
			0b01111100,
			0b11111100,
			0b00001110,
			0b11111110,
			0b01111110
	};

	Gpio *_sels[SELS_COUNT];
	uint32_t _seg_port;
	uint8_t _current_indicator_index = 0;

	void _select(uint8_t indicator_index);
	void _deselect(uint8_t indicator_index);

};
}
