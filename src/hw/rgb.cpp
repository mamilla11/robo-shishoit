#include "rgb.h"

namespace hw {

Rgb::Rgb(uint32_t port_r, uint16_t pin_r,
		 uint32_t port_g, uint16_t pin_g,
		 uint32_t port_b, uint16_t pin_b,
		 Logic logic) : _logic(logic)
{
	_leds[0] = new Gpio(port_r, pin_r, Gpio::Mode::Output10MHz, Gpio::Type::OutputPushPull);
	_leds[1] = new Gpio(port_g, pin_g, Gpio::Mode::Output10MHz, Gpio::Type::OutputPushPull);
	_leds[2] = new Gpio(port_b, pin_b, Gpio::Mode::Output10MHz, Gpio::Type::OutputPushPull);
}

void Rgb::on(Color color)
{
	uint8_t mask = static_cast<uint8_t>(color);

	for(int i = 0; i < LEDS_COUNT; i++) {
		if ((mask & 0b001) == 0b001) {
			_logic == Logic::STRAIGHT ? _leds[i]->set() : _leds[i]->clear();
	    }
	    else {
	    	_logic == Logic::STRAIGHT ? _leds[i]->clear() : _leds[i]->set();
	    }

	    mask = mask >> 1;
	}
}

void Rgb::off() {
	for (int i = 0; i < LEDS_COUNT; i++) {
		_logic == Logic::STRAIGHT ? _leds[i]->clear() : _leds[i]->set();
	}
}

void Rgb::set_start_color(Color color) {
	_current_color = color;
}

void Rgb::set_next_color()
{
	off();
	on(_current_color);

	uint8_t color_index = static_cast<uint8_t>(_current_color) + 1;
	if (color_index > COLORS_COUNT) {
		color_index = 1;
	}

	 _current_color = static_cast<Color>(color_index);
}

}

