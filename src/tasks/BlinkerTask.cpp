#include "BlinkerTask.h"
#include <stdlib.h>

namespace tasks {

BlinkerTask::BlinkerTask()
 {
	_timerMs = new hw::TimerMs(hw::TimerMs::TimerMode::CYCLE, 20);

	_pwm = new hw::PWMTimer(config::BLINKER_TIM, _BLINKER_PERIOD_US);
	_pwm->setupChannel(config::BLINKER_R_PORT, config::BLINKER_R_PIN, _CHANNEL_R);
	_pwm->setupChannel(config::BLINKER_G_PORT, config::BLINKER_G_PIN, _CHANNEL_G);
	_pwm->setupChannel(config::BLINKER_B_PORT, config::BLINKER_B_PIN, _CHANNEL_B);
	_pwm->on();

	_setRandomColor();
}

void BlinkerTask::process() {
	if (_timerMs->timeout()) {
		_changeIntensity();
	}
}

void BlinkerTask::_setRandomColor() {
	_setRandomDutySteps();
	_setDutyCycle(10, 10, 10);

	if (rand() % 2 == 0) {
		_disableRandomColor();
	}
}

void BlinkerTask::_changeIntensity() {
	static uint8_t i = 0;

	if (_direction == BlinkerDirection::UP) {
		_increaseDutyCycle(rDutyStep, gDutyStep, bDutyStep);
		i++;

		if (i == _DUTY_STEPS_COUNT) {
			_direction = BlinkerDirection::DOWN;
		}
	} else {
		_decreaseDutyCycle(rDutyStep, gDutyStep, bDutyStep);
		i--;

		if (i == 0) {
			_direction = BlinkerDirection::UP;
			_setRandomColor();
		}
	}
}

void BlinkerTask::_setDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty) {
	_pwm->setDutyCycle(_CHANNEL_R, rDuty);
	_pwm->setDutyCycle(_CHANNEL_G, gDuty);
	_pwm->setDutyCycle(_CHANNEL_B, bDuty);
}

void BlinkerTask::_increaseDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty) {
	_pwm->increaseDutyCycle(_CHANNEL_R, rDuty);
	_pwm->increaseDutyCycle(_CHANNEL_G, gDuty);
	_pwm->increaseDutyCycle(_CHANNEL_B, bDuty);
}

void BlinkerTask::_decreaseDutyCycle(uint16_t rDuty, uint16_t gDuty, uint16_t bDuty) {
	_pwm->decreaseDutyCycle(_CHANNEL_R, rDuty);
	_pwm->decreaseDutyCycle(_CHANNEL_G, gDuty);
	_pwm->decreaseDutyCycle(_CHANNEL_B, bDuty);
}

void BlinkerTask::_disableRandomColor() {
	switch (rand() % 3) {
		case 0:
			rDutyStep = 0;
			_pwm->setDutyCycle(_CHANNEL_R, 0);
			break;
		case 1:
			gDutyStep = 0;
			_pwm->setDutyCycle(_CHANNEL_G, 0);
			break;
		case 2:
			bDutyStep = 0;
			_pwm->setDutyCycle(_CHANNEL_B, 0);
			break;
	}
}

void BlinkerTask::_setRandomDutySteps() {
	rDutyStep = 0;
	gDutyStep = 0;
	bDutyStep = 0;

	while ((abs(rDutyStep - gDutyStep) < 5) &&
		   (abs(rDutyStep - bDutyStep) < 5) &&
		   (abs(gDutyStep - bDutyStep) < 5)) {
		rDutyStep = rand() % (_MAX_DUTY_STEP + 1);
		gDutyStep = rand() % (_MAX_DUTY_STEP + 1);
		bDutyStep = rand() % (_MAX_DUTY_STEP + 1);
	}
}

}
