#pragma once

#include "base/TaskBase.hpp"
#include "base/Message.hpp"

#include <config/TaskConfig.h>
#include <hw/ModeSwitcher.h>
#include <hw/Backlight.hpp>
#include <hw/PWMTimer.h>
#include <hw/Buttons.h>
#include <hw/Time.h>

namespace tasks {

namespace msg {

enum class LogicEvent : uint8_t {
	IDLE,
	EYES_SETUP,
	TIME_SETUP,
	LEFT_BUTTON_PRESSED,
	RIGHT_BUTTON_PRESSED,
	UPDATE_TIME,
};

using LogicMessage = base::Event<LogicEvent>;

}

class LogicTask final : public base::TaskBase<config::tasks::LogicTask::NAME,
		         	 	msg::LogicMessage,
						config::tasks::LogicTask::FIFO_SIZE> {

public:
	LogicTask();
	~LogicTask() = default;

	void Run();

private:
	enum class State : uint8_t {
		IDLE,
		EYES_SETUP,
		TIME_SETUP
	};

	enum class Color : uint8_t {
		RED = 0,
		GREEN,
		BLUE,
		MAGENTA,
		CYAN,
		YELLOW,
		WHITE,

		COUNT
	};

	static const hw::PWMTimer::Channel _CHANNEL_R = hw::PWMTimer::Channel::CH1;
	static const hw::PWMTimer::Channel _CHANNEL_G = hw::PWMTimer::Channel::CH2;
	static const hw::PWMTimer::Channel _CHANNEL_B = hw::PWMTimer::Channel::CH3;

	static constexpr uint8_t EYES_MIN_DUTY_CYCLE = 0;
	static constexpr uint8_t EYES_MAX_DUTY_CYCLE = 255;
	static constexpr uint8_t EYES_DUTY_CYCLE_STEP = 25;

	static constexpr uint16_t _EYES_PERIOD_US = 255;

	hw::PWMTimer * _eyesColorPWM;
	Color _eyesColor = Color::YELLOW;
	uint8_t _eyesIntensity = 0;
	State _state = State::IDLE;
	hw::ModeSwitcher _switcher;
	hw::Backlight _backlight;
	hw::Buttons _buttons;
	hw::Time _time;
	uint8_t _hours = 0;
	uint8_t _minutes = 0;

	void _leftButtonPressedHandler();
	void _rightButtonPressedHandler();

	void _updateTime();
	void _displayHours(uint8_t hours, bool dotted = true);
	void _displayMinutes(uint8_t minutes);
	void _displayNextHour();
	void _displayNextMinute();
	void _saveTime();

	void _setEyesColor(Color color);
	void _setNextEyesColor();
	void _setEyesIntensity();
};

}

