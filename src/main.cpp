#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	//gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6 | GPIO8);
	gpio_set(GPIOC, GPIO6);
	gpio_clear(GPIOC, GPIO8);

	while(1) {
		gpio_toggle(GPIOC, GPIO6);
		gpio_toggle(GPIOC, GPIO8);
		for (int i = 0; i < 800000; i++)
			__asm__("nop");
	}

	return 0;
}
