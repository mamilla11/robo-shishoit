#pragma once

#include <libopencm3/stm32/rcc.h>

namespace config {

inline void ClockInit() {
	rcc_clock_setup_in_hse_16mhz_out_72mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM3); //blinker PWM
	rcc_periph_clock_enable(RCC_TIM2); //eyes PWM
	rcc_periph_clock_enable(RCC_TIM1); //long press detection
	rcc_periph_clock_enable(RCC_PWR);
	rcc_periph_clock_enable(RCC_BKP);
}

}

