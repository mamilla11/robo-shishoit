#include "LogicTask.h"
#include "BlinkerTask.h"
#include "DisplayTask.h"

namespace tasks {

LogicTask::LogicTask() :
		TaskBase(config::tasks::LogicTask::STACK_SIZE,
				 config::tasks::LogicTask::PRIORITY),
				 _touch(hw::Touch()),
				 _backlight(hw::Backlight()),
				 _buttons(hw::Buttons()),
				 _time(hw::Time())
{

	hw::HandLed();
	_eyesColorPWM = new hw::PWMTimer(config::EYES_TIM, _EYES_PERIOD_US);
	_eyesColorPWM->setupChannel(config::EYES_R_PORT, config::EYES_R_PIN, _CHANNEL_R);
	_eyesColorPWM->setupChannel(config::EYES_G_PORT, config::EYES_G_PIN, _CHANNEL_G);
	_eyesColorPWM->setupChannel(config::EYES_B_PORT, config::EYES_B_PIN, _CHANNEL_B);
	_eyesColorPWM->on();
	_setEyesColor(_eyesColor);

	this->Start();
}

void LogicTask:: Run() {
	while(true) {
		_blocking_read();

		switch (_fifo_data.token) {
			case msg::LogicEvent::TOUCH_PRESSED:
				_setNextEyesColor();
				break;
			case msg::LogicEvent::LEFT_BUTTON_LONG_PRESS:
				_switchState();
				break;
			case msg::LogicEvent::LEFT_BUTTON_PRESSED:
				_leftButtonPressedHandler();
				break;
			case msg::LogicEvent::RIGHT_BUTTON_PRESSED:
				_rightButtonPressedHandler();
				break;
			case msg::LogicEvent::UPDATE_TIME:
				_updateTime();
				break;
			default:
				break;
		}
	}
}

void LogicTask::_leftButtonPressedHandler() {
	switch (_state) {
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
	}
}

void LogicTask::_updateTime() {

	static bool dotted = false;

	if (_state != State::IDLE)
		return;

	_hours = _time.getHours();
	_minutes = _time.getMinutes();

	_displayHours(_hours, dotted);
	_displayMinutes(_minutes);
	dotted = !dotted;
}

void LogicTask::_displayHours(uint8_t hours, bool dotted) {
	DisplayTask::setChar(0, (hours / 10 % 10));
	DisplayTask::setChar(1, (hours % 10), dotted);
}

void LogicTask::_displayMinutes(uint8_t minutes) {
	DisplayTask::setChar(2, (minutes / 10 % 10));
	DisplayTask::setChar(3, (minutes % 10));
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

void LogicTask::_setEyesColor(Color color) {
	switch (color) {
		case Color::RED:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, EYES_MAX_DUTY_CYCLE);
			break;
		case Color::GREEN:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, EYES_MAX_DUTY_CYCLE);
			break;
		case Color::BLUE:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, _eyesIntensity);
			break;
		case Color::MAGENTA:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, _eyesIntensity);
			break;
		case Color::CYAN:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, EYES_MAX_DUTY_CYCLE);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, _eyesIntensity);
			break;
		case Color::YELLOW:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, EYES_MAX_DUTY_CYCLE);
			break;
		case Color::WHITE:
			_eyesColorPWM->setDutyCycle(_CHANNEL_R, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_G, _eyesIntensity);
			_eyesColorPWM->setDutyCycle(_CHANNEL_B, _eyesIntensity);
			break;
		default: break;
	}
}

void LogicTask::_setNextEyesColor() {
	_eyesColor = (Color)((uint8_t)_eyesColor + 1);

	if (_eyesColor == Color::COUNT) {
		_eyesColor = Color::RED;
	}

	_setEyesColor(_eyesColor);
}

}
