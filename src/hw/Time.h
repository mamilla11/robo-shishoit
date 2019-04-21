#pragma once

#include <config/HwConfig.h>

extern "C" void rtc_isr(void);

namespace hw {

class Time {
public:
	Time();
	~Time() = default;

	uint8_t getSeconds();
	uint8_t getMinutes();
	uint8_t getHours();

	void setTime(uint8_t hours, uint8_t minutes);

private:
	static constexpr uint32_t _SECONDS_IN_DAY = 86399;
	void _restoreTime();
};

}

