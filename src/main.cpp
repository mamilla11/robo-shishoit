#include "config/clock.hpp"
#include "config/hw_config.h"
#include "hw/systick.h"
#include "hw/counter.h"
#include "hw/rgb.h"
#include "hw/indicators.h"

int main(void)
{
	config::clock_init();
	config::swj_disable();

	hw::systick::systick_init(config::SYSTEM_CORE_CLOCK,
					 config::SYSTEM_CORE_CLOCK_DIV);


	hw::Rgb *eyes = new hw::Rgb(config::EYES_R_PORT, config::EYES_R_PIN,
						   config::EYES_G_PORT, config::EYES_G_PIN,
			               config::EYES_B_PORT, config::EYES_B_PIN);
	eyes->off();

	hw::Rgb *blinker = new hw::Rgb(config::BLINKER_R_PORT, config::BLINKER_R_PIN,
						      config::BLINKER_G_PORT, config::BLINKER_G_PIN,
			                  config::BLINKER_B_PORT, config::BLINKER_B_PIN,
							  hw::Rgb::Logic::INVERSE);
	blinker->off();

	hw::Indicators indicators = hw::Indicators(config::CHAR_SEL_PORTS,
											   config::CHAR_SEL_PINS,
											   config::CHAR_SEG_PORT);

	uint8_t indicatorsValue = 0;
	indicators.set_number(indicatorsValue);

	hw::Counter timer1s = hw::Counter(hw::Counter::Mode::CYCLE, 1000);
	hw::Counter timer1ms = hw::Counter(hw::Counter::Mode::CYCLE, 1);

	while(1) {
		if (timer1s.timeout()) {
			blinker->set_next_color();
			eyes->set_next_color();
			if (++indicatorsValue == 10) {
				indicatorsValue = 0;
			}
			indicators.set_number(indicatorsValue);
		}

		if (timer1ms.timeout()) {
			indicators.set_next_indicator();
		}
	}

	return 0;
}
