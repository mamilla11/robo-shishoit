#pragma once

#include <libopencm3/stm32/gpio.h>

namespace hw {
	class Gpio {
	public:
		enum class Mode : uint8_t {
			Output10MHz = GPIO_MODE_OUTPUT_10_MHZ,
			Output50MHz = GPIO_MODE_OUTPUT_50_MHZ,
		};

		enum class Type : uint8_t {
			OutputPushPull = GPIO_CNF_OUTPUT_PUSHPULL,
			OutputAltPushPull = GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
			OutputOpenDrain = GPIO_CNF_OUTPUT_OPENDRAIN
		};

		Gpio(uint32_t port, uint32_t pin, Mode mode, Type type);
		~Gpio() = default;

		void set();
		void clear();
		void toggle();

	private:
		uint32_t _port;
		uint32_t _pin;
	};
}
