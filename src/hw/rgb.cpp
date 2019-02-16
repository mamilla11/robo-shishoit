#include "rgb.h"

namespace hw {

Rgb::Rgb(uint32_t _port_r, uint32_t _pin_r,
		 uint32_t _port_g, uint32_t _pin_g,
		 uint32_t _port_b, uint32_t _pin_b)
{
	_leds[0] = new Led(_port_r, _pin_r);
	_leds[1] = new Led(_port_g, _pin_g);
	_leds[2] = new Led(_port_b, _pin_b);
}

void Rgb::on(Color color)
{
	uint8_t mask = static_cast<uint8_t>(color);

	for(int i = 0; i < LEDS_COUNT; i++) {
		if ((mask & 0b001) == 0b001) {
			_leds[i]->set();
	    }
	    else {
	    	_leds[i]->clear();
	    }

	    mask = mask >> 1;
	}
}

void Rgb::off() {
	for (int i = 0; i < LEDS_COUNT; ++i) {
		_leds[i]->clear();
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

