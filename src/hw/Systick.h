#pragma once

#include <libopencm3/cm3/systick.h>

extern "C" void sys_tick_handler(void);
extern "C" void delay_nop(uint32_t count);

namespace hw {

static constexpr uint32_t SYSTEM_CORE_CLOCK = 72000000;
static constexpr uint32_t SYSTEM_CORE_CLOCK_DIV = 1000;

void SystickInit();
void delay_ms(uint32_t ms);
uint32_t get_counter_ms();

}
