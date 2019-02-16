#pragma once

#include <libopencm3/stm32/gpio.h>

namespace hw {
	class Led {
	public:
		Led(uint32_t port, uint32_t pin);
		~Led() = default;

		void set();
		void clear();
		void toggle();

	private:
		uint32_t _port;
		uint32_t _pin;
		static const uint32_t _MODE = GPIO_MODE_OUTPUT_10_MHZ;
		static const uint32_t _OUTPUT_TYPE = GPIO_CNF_OUTPUT_PUSHPULL;
	};
}
