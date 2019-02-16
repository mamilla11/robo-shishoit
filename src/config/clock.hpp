#pragma once

#include <libopencm3/stm32/rcc.h>

namespace config {
inline void clock_init() {
	rcc_clock_setup_in_hse_16mhz_out_72mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
}
}

