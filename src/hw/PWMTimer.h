#pragma once

#include <cstdint>
#include <libopencm3/stm32/timer.h>

namespace hw {

class PWMTimer {
public:
	PWMTimer(uint32_t timer, uint32_t period);
	~PWMTimer() = default;

	enum class Channel : uint8_t {
		CH1 = tim_oc_id::TIM_OC1,
		CH2 = tim_oc_id::TIM_OC2,
		CH3 = tim_oc_id::TIM_OC3,
		CH4 = tim_oc_id::TIM_OC4,
	};

	void setupChannel(uint32_t port, uint16_t pin, Channel channel);
	void setDutyCycle(Channel channel, uint16_t value);
	void increaseDutyCycle(Channel channel, uint16_t value);
	void decreaseDutyCycle(Channel channel, uint16_t value);
	uint16_t getDutyCycle(Channel channel);
	void on();
	void off();

private:
	uint32_t _timer;
	uint32_t _period;
	void _setupTimer();
};

}
