#pragma once

#include "base/TaskBase.hpp"
#include "base/Message.hpp"

#include <config/TaskConfig.h>
#include <hw/PWMTimer.h>

namespace tasks {

namespace msg {

enum class BlinkerEvent : uint8_t {
	EYES_SETUP,
	TIME_SETUP,
	SETUP_FINISHED,
	WAIT,
};

using BlinkerMessage = base::Event<BlinkerEvent>;

}

class BlinkerTask final : base::TaskBase<config::tasks::BlinkerTask::NAME,
		         	 	  msg::BlinkerMessage,
						  config::tasks::BlinkerTask::FIFO_SIZE> {
public:
	BlinkerTask();
	~BlinkerTask() = default;

	void Run();

private:
	static const hw::PWMTimer::Channel _CHANNEL_R = hw::PWMTimer::Channel::CH1;
	static const hw::PWMTimer::Channel _CHANNEL_G = hw::PWMTimer::Channel::CH2;
	static const hw::PWMTimer::Channel _CHANNEL_B = hw::PWMTimer::Channel::CH3;

	static constexpr uint16_t _BLINKER_PERIOD_US = 600;
	static constexpr uint8_t _DELAY_BASE_TICKS = 2;
	static constexpr uint8_t _MAX_DUTY_STEP = 20;
	static constexpr uint8_t _DUTY_STEPS_COUNT = _BLINKER_PERIOD_US / _MAX_DUTY_STEP - 1;

	hw::PWMTimer * _pwm;
	uint8_t rDutyStep = 0;
	uint8_t gDutyStep = 0;
	uint8_t bDutyStep = 0;

	void _setNextColor();
	void _setRedColor();
	void _setGreenColor();

	void _delay(uint32_t ticks);
	void _setDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty);
	void _increaseDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty);
	void _decreaseDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty);
	void _disableRandomColor();
	void _setRandomDutySteps();
};

}
