#pragma once

#include <config/HwConfig.h>

namespace hw
{
class Display {
public:
	Display();
	~Display() = default;
	void setNextChar();
	void setCharValue(uint8_t char_i, uint8_t value, bool dotted = false);

private:
	static constexpr uint8_t CHAR_COUNT = 4;
	static constexpr uint16_t NUMBER_MASK = 0x00FF;
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

	uint32_t _numberPort = config::CHAR_SEG_PORT;

	uint16_t _char_1_value = NUMBERS[0];
	uint16_t _char_2_value = NUMBERS[0];
	uint16_t _char_3_value = NUMBERS[0];
	uint16_t _char_4_value = NUMBERS[0];

	void _setNumber(uint16_t number);
	void _select(uint8_t char_i);
	void _deselect(uint8_t char_i);
	void _deselectAll();

	void _setupGpio();

};
}
