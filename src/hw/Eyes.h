#pragma once

#include <config/HwConfig.h>
#include <hw/PWMTimer.h>

namespace hw {

class Eyes {
public:
	Eyes();
	~Eyes() = default;

	enum class Color {
		RED,
		GREEN,
		BLUE,
		MAGENTA,
		CYAN,
		YELLOW,
		WHITE,

		COUNT
	};

	Color currentColor = Color::YELLOW;

	void setNextColor();
	void setColor(Color color);
	void blink();
	void on();
	void off();

private:
	static const hw::PWMTimer::Channel _CHANNEL_R = hw::PWMTimer::Channel::CH1;
	static const hw::PWMTimer::Channel _CHANNEL_G = hw::PWMTimer::Channel::CH2;
	static const hw::PWMTimer::Channel _CHANNEL_B = hw::PWMTimer::Channel::CH3;

	static const uint32_t _MAX_DUTY_CYCLE = 255;
	static const uint32_t _PERIOD_US      = 255;

	PWMTimer * _pwmTimer;
	uint32_t _intensity = 0;

	uint32_t _rDuty = 0;
	uint32_t _gDuty = 0;
	uint32_t _bDuty = 0;
};

}
