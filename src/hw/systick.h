#pragma once

#include <libopencm3/cm3/systick.h>

namespace hw {
namespace systick {
extern "C" void sys_tick_handler(void);
extern "C" void delay_nop(uint32_t count);

void systick_init(uint32_t core_freq, uint32_t div);
uint32_t get_counter_ms();
void delay_ms(uint32_t ms);
}
}
