#pragma once

#include "base/TaskBase.hpp"
#include "base/Message.hpp"

#include <config/TaskConfig.h>
#include <hw/Backlight.hpp>
#include <hw/HandLed.hpp>
#include <hw/Eyes.h>
#include <hw/Buttons.h>
#include <hw/Time.h>
#include <hw/Touch.h>

namespace tasks {

namespace msg {

enum class LogicEvent : uint8_t {
	TOUCH_PRESSED,
	LEFT_BUTTON_LONG_PRESS,
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
		TIME_SETUP
	};

	State _state = State::IDLE;
	hw::Touch _touch;
	hw::Backlight _backlight;
	hw::HandLed _handLed;
	hw::Eyes _eyes;
	hw::Buttons _buttons;
	hw::Time _time;
	uint8_t _hours = 0;
	uint8_t _minutes = 0;

	void _leftButtonPressedHandler();
	void _rightButtonPressedHandler();
	void _switchState();
	void _updateTime();
	void _displayHours(uint8_t hours, bool dotted = true);
	void _displayMinutes(uint8_t minutes);
	void _displayNextHour();
	void _displayNextMinute();
	void _saveTime();
};

}

