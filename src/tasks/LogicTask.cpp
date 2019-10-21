#include "LogicTask.h"

namespace tasks {

LogicTask::LogicTask() :
				 _robo(hw::Robo()),
				 _eyes(hw::Eyes()),
				 _time(hw::Time()),
				 _display(hw::Display())
{
	_updateTimeTimer = new hw::TimerMs(hw::TimerMs::TimerMode::CYCLE, 1000);
	_eyesBlinkTimer = new hw::TimerMs(hw::TimerMs::TimerMode::CYCLE, 250);
	_pollingButtonsTimer = new hw::TimerMs(hw::TimerMs::TimerMode::CYCLE, 50);
}

void LogicTask::process() {
	if (_updateTimeTimer->timeout()) {
		_updateTime();
	}

	if ((_eyesBlinkTimer->timeout()) && (_state == State::TIME_SETUP)) {
		_eyes.blink();
	}

	if (_pollingButtonsTimer->timeout()) {
		_pollingButtons();
	}

	_display.setNextChar();
}

void LogicTask::_leftButtonPressedHandler() {
	switch (_state) {
		case State::IDLE:
			_robo.toggleBacklight();
			break;
		case State::TIME_SETUP:
			_displayNextHour();
			_saveTime();
			break;
		default:
			break;
	}
}

void LogicTask::_rightButtonPressedHandler() {
	switch (_state) {
		case State::IDLE:
			_robo.toggleHandLed();
			break;
		case State::TIME_SETUP:
			_displayNextMinute();
			_saveTime();
			break;
		default:
			break;
	}
}

void LogicTask::_switchState() {
	if (_state == State::IDLE) {
		_state = State::TIME_SETUP;
	} else {
		_state = State::IDLE;
		_eyes.on();
	}
}

void LogicTask::_updateTime() {
	static bool dotted = false;

	if (_state == State::IDLE) {
		_hours = _time.getHours();
		_minutes = _time.getMinutes();

		_displayHours(_hours, dotted);
		_displayMinutes(_minutes);
		dotted = !dotted;
	}
}

void LogicTask::_pollingButtons() {
	static const uint8_t LONG_PRESS_DETECTED_VALUE = 40;

	static bool touchPressedPrev   = false;
	static bool lButtonPressedPrev = false;
	static bool rButtonPressedPrev = false;

	static uint8_t touchPressCounter        = 0;
	static uint8_t lButtonShortPressCounter = 0;
	static uint8_t rButtonShortPressCounter = 0;

	static uint8_t lButtonLongPressCounter = 0;

	bool touchPressedCurr   = _robo.isTouchPressed();

	if (touchPressedCurr != touchPressedPrev) {
		touchPressedPrev = touchPressedCurr;
		touchPressCounter++;
	}

	if (touchPressCounter == 2) {
		touchPressCounter = 0;
		_eyes.setNextColor();
	}

	bool rButtonPressedCurr = _robo.isRightButtonPressed();

	if (rButtonPressedCurr != rButtonPressedPrev) {
		rButtonPressedPrev = rButtonPressedCurr;
		rButtonShortPressCounter++;
	}

	if (rButtonShortPressCounter == 2) {
		rButtonShortPressCounter = 0;
		_rightButtonPressedHandler();
	}

	bool lButtonPressedCurr = _robo.isLeftButtonPressed();

	if (lButtonPressedCurr != lButtonPressedPrev) {
		lButtonPressedPrev = lButtonPressedCurr;
		lButtonShortPressCounter++;
	}

	if (lButtonShortPressCounter == 2) {
		lButtonShortPressCounter = 0;
		if (lButtonLongPressCounter < LONG_PRESS_DETECTED_VALUE) {
			_leftButtonPressedHandler();
		}
		lButtonLongPressCounter = 0;
	}

	if ((lButtonPressedCurr == lButtonPressedPrev) && (lButtonPressedCurr == true)) {
		lButtonLongPressCounter++;
	}

	if (lButtonLongPressCounter == LONG_PRESS_DETECTED_VALUE) {
		_switchState();
	}
}

void LogicTask::_displayHours(uint8_t hours, bool dotted) {
	_display.setCharValue(0, (hours / 10 % 10));
	_display.setCharValue(1, (hours % 10), dotted);
}

void LogicTask::_displayMinutes(uint8_t minutes) {
	_display.setCharValue(2, (minutes / 10 % 10));
	_display.setCharValue(3, (minutes % 10));
}

void LogicTask::_displayNextHour() {
	_hours++;

	if (_hours >= 24)
		_hours = 0;

	_displayHours(_hours);
}

void LogicTask::_displayNextMinute() {
	_minutes++;

	if (_minutes >= 60) {
		_minutes = 0;
	}

	_displayMinutes(_minutes);
}

void LogicTask::_saveTime() {
	_time.setTime(_hours, _minutes);
}

}
