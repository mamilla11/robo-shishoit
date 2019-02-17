#pragma once

#include <hw/gpio.h>

namespace hw {
	class Rgb {
	public:
		enum class Color : uint8_t {
			RED		= 0b001,
			GREEN   = 0b010,
			BLUE	= 0b100,
			MAGENTA = RED  | BLUE,
			CYAN    = BLUE | GREEN,
			YELLOW  = RED  | GREEN,
			WHITE	= RED  | GREEN  | BLUE
		};

		enum class Logic : uint8_t {
			STRAIGHT,
			INVERSE
		};

		Rgb(uint32_t port_r, uint16_t pin_r,
			uint32_t port_g, uint16_t pin_g,
			uint32_t port_b, uint16_t pin_b,
			Logic logic = Logic::STRAIGHT);

		~Rgb() = default;

		void on(Color color);
		void off();

		void set_next_color();
		void set_start_color(Color color);

	private:
		constexpr static uint8_t LEDS_COUNT = 3;
		constexpr static uint8_t COLORS_COUNT = 7;

		Gpio *_leds[LEDS_COUNT];
		Color _current_color = Color::RED;
		Logic _logic = Logic::STRAIGHT;
	};
}
