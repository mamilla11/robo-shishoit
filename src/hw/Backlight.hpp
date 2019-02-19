#pragma once

#include <config/HwConfig.h>

namespace hw {

class Backlight {
public:
	Backlight() {
		gpio_set_mode(config::BACKLIGHT_PORT, GPIO_MODE_OUTPUT_50_MHZ,
				                      GPIO_CNF_OUTPUT_PUSHPULL, config::BACKLIGHT_PIN);
		gpio_set(config::BACKLIGHT_PORT, config::BACKLIGHT_PIN);
	}
	~Backlight() = default;
};

}
