#pragma once

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

namespace config {

static constexpr uint32_t SYSTEM_CORE_CLOCK = 72000000;
static constexpr uint32_t SYSTEM_CORE_CLOCK_DIV = 1000;

inline void ClockInit() {
	rcc_clock_setup_in_hse_16mhz_out_72mhz();

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM2);
}

inline void SystickInit()
{
    systick_set_reload(SYSTEM_CORE_CLOCK / SYSTEM_CORE_CLOCK_DIV);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    systick_interrupt_enable();
}

}

