#include "Time.h"

#include "Backlight.hpp"

namespace hw {

Time *timePointer;

Time::Time() {
	timePointer = this;
	rtc_auto_awake(config::RTC_SOURCE, config::RTC_PRESCALER);
	rtc_set_alarm_time(86399);

	nvic_enable_irq(NVIC_RTC_IRQ);
	rtc_interrupt_enable(RTC_ALR);
}

uint8_t Time::getSeconds() {
	uint32_t counter = rtc_get_counter_val();
	return (counter % 3600) % 60;
}

uint8_t Time::getMinutes() {
	uint32_t counter = rtc_get_counter_val();
	return (counter % 3600) / 60;
}

uint8_t Time::getHours() {
	uint32_t counter = rtc_get_counter_val();
	return counter / 3600;
}

void Time::setTime(uint8_t hours, uint8_t minutes) {
	uint32_t counter = (hours * 3600) + (minutes * 60);
	rtc_set_counter_val(counter);
}

}

void rtc_isr(void) {
	if (rtc_check_flag(RTC_ALR) > 0) {
		rtc_clear_flag(RTC_ALR);
		rtc_set_counter_val(0);
	}
}
