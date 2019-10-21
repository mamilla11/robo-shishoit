#include "Systick.h"

namespace hw {

static volatile uint32_t counter_ms;

void SystickInit()
{
	counter_ms = 0;
    systick_set_reload(SYSTEM_CORE_CLOCK / SYSTEM_CORE_CLOCK_DIV);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    systick_interrupt_enable();
}

void delay_ms(uint32_t ms)
{
	uint32_t time = counter_ms;
	while((counter_ms - time) < ms);
}

uint32_t get_counter_ms()
{
	return counter_ms;
}

}

void sys_tick_handler(void)
{
	hw::counter_ms++;
}

void delay_nop(uint32_t count)
{
	while(count--) {
		__asm("nop");
	}
}
