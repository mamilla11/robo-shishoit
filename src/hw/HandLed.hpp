
#pragma once

#include <config/HwConfig.h>

namespace hw {

class HandLed {
public:
	HandLed() {
		gpio_set_mode(config::HANDLED_PORT, GPIO_MODE_OUTPUT_50_MHZ,
				                      GPIO_CNF_OUTPUT_PUSHPULL, config::HANDLED_PIN);
		gpio_set(config::BACKLIGHT_PORT, config::BACKLIGHT_PIN);
	}
	~HandLed() = default;
};

}
