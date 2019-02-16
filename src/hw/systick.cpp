#include "systick.h"

namespace hw {
namespace systick {
volatile uint32_t counter_ms;

void sys_tick_handler(void)
{
	counter_ms++;
}

void delay_nop(uint32_t count)
{
	while(count--) { __asm("nop"); }
}

void delay_ms(uint32_t ms)
{
	uint32_t time = counter_ms;
	while((counter_ms - time) < ms);
}

void systick_init(uint32_t core_freq, uint32_t div)
{
	counter_ms = 0;
	systick_set_reload(core_freq / div);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();
}

uint32_t get_counter_ms()
{
	return counter_ms;
}
}
}



