#include "config/clock.hpp"
#include "config/hw_config.h"
#include "hw/systick.h"
#include "hw/counter.h"
#include "hw/rgb.h"

int main(void)
{
	config::clock_init();

	hw::systick::systick_init(config::SYSTEM_CORE_CLOCK,
					 config::SYSTEM_CORE_CLOCK_DIV);


	hw::Rgb eyes = hw::Rgb(config::EYES_R_PORT, config::EYES_R_PIN,
						   config::EYES_G_PORT, config::EYES_G_PIN,
			               config::EYES_B_PORT, config::EYES_B_PIN);

	eyes.on(hw::Rgb::Color::MAGENTA);

	hw::Rgb blinker = hw::Rgb(config::BLINKER_R_PORT, config::BLINKER_R_PIN,
						      config::BLINKER_G_PORT, config::BLINKER_G_PIN,
			                  config::BLINKER_B_PORT, config::BLINKER_B_PIN);
	blinker.off();

	hw::Counter blinkerTimer = hw::Counter(hw::Counter::Mode::CYCLE, 1000);

	while(1) {
		if (blinkerTimer.timeout()) {
			blinker.set_next_color();
		}
	}

	return 0;
}
