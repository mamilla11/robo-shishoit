#include "led.h"

namespace hw
{
Led::Led(uint32_t port, uint32_t pin) : _port(port), _pin(pin)
{
	gpio_set_mode(_port, _MODE, _OUTPUT_TYPE, _pin);
}

void Led::set() {
	gpio_set(_port, _pin);

}

void Led::clear() {
	gpio_clear(_port, _pin);
}

void Led::toggle() {
	gpio_toggle(_port, _pin);
}
}



