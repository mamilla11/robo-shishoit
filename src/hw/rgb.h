#pragma once

#include <hw/led.h>

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

		Rgb(uint32_t _port_r, uint32_t _pin_r,
			uint32_t _port_g, uint32_t _pin_g,
			uint32_t _port_b, uint32_t _pin_b);
		~Rgb() = default;

		void on(Color color);
		void off();

		void set_next_color();
		void set_start_color(Color color);

	private:
		constexpr static uint8_t LEDS_COUNT = 3;
		constexpr static uint8_t COLORS_COUNT = 7;

		Led *_leds[LEDS_COUNT];
		Color _current_color = Color::RED;
	};
}
