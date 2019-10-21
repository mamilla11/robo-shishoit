#pragma once

#include <hw/Robo.h>
#include <hw/Eyes.h>
#include <hw/Time.h>
#include <hw/Display.h>
#include <hw/TimerMs.h>

namespace tasks {

class LogicTask {

public:
	LogicTask();
	~LogicTask() = default;

	void process();

private:
	enum class State : uint8_t {
		IDLE,
		TIME_SETUP
	};

	State _state = State::IDLE;
	hw::Robo      _robo;
	hw::Eyes      _eyes;
	hw::Time      _time;
	hw::Display   _display;
	hw::TimerMs * _updateTimeTimer;
	hw::TimerMs * _eyesBlinkTimer;
	hw::TimerMs * _pollingButtonsTimer;
	uint8_t       _hours = 0;
	uint8_t       _minutes = 0;

	void _leftButtonPressedHandler();
	void _rightButtonPressedHandler();
	void _switchState();
	void _updateTime();
	void _pollingButtons();
	void _displayHours(uint8_t hours, bool dotted = true);
	void _displayMinutes(uint8_t minutes);
	void _displayNextHour();
	void _displayNextMinute();
	void _saveTime();
};

}

