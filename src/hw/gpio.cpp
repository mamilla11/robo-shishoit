#include <hw/gpio.h>

namespace hw
{
Gpio::Gpio(uint32_t port, uint32_t pin, Mode mode, Type type)
	: _port(port),
	  _pin(pin)
{
	gpio_set_mode(_port, static_cast<uint8_t>(mode),
			      static_cast<uint8_t>(type), _pin);
}

void Gpio::set() {
	gpio_set(_port, _pin);

}

void Gpio::clear() {
	gpio_clear(_port, _pin);
}

void Gpio::toggle() {
	gpio_toggle(_port, _pin);
}
}



