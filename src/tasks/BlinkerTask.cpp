#include "BlinkerTask.h"
#include <config/HwConfig.h>
#include <stdlib.h>

namespace tasks {

BlinkerTask::BlinkerTask() : TaskBase(config::tasks::BlinkerTask::STACK_SIZE,
									  config::tasks::BlinkerTask::PRIORITY) {

	_pwm = new hw::PWMTimer(config::BLINKER_TIM, _BLINKER_PERIOD_US);
	_pwm->setupChannel(config::BLINKER_R_PORT, config::BLINKER_R_PIN, _CHANNEL_R);
	_pwm->setupChannel(config::BLINKER_G_PORT, config::BLINKER_G_PIN, _CHANNEL_G);
	_pwm->setupChannel(config::BLINKER_B_PORT, config::BLINKER_B_PIN, _CHANNEL_B);
	_pwm->on();

	this->Start();
}

void BlinkerTask::Run() {
	_setNextColor();

	while(true) {
		_blocking_read();

		switch (_fifo_data.token) {
		case  msg::BlinkerMessage::Token::WAIT:
			_setNextColor();
			break;
		case  msg::BlinkerMessage::Token::EYES_SETUP:
			fifo_flush();
			_setRedColor();
			break;
		case  msg::BlinkerMessage::Token::TIME_SETUP:
			fifo_flush();
			_setGreenColor();
			break;
		case  msg::BlinkerMessage::Token::SETUP_FINISHED:
			_setNextColor();
			break;
		}
	}
}

void BlinkerTask::_setNextColor() {
	_setRandomDutySteps();
	_setDutyCycle(10, 10, 10);

	if (rand() % 2 == 0) {
		_disableRandomColor();
	}

	for (uint8_t i = 0; i < _DUTY_STEPS_COUNT; i++) {
		_increaseDutyCycle(rDutyStep, gDutyStep, bDutyStep);
		_delay(_DELAY_BASE_TICKS + i / 4);
	}

	for (uint8_t i = _DUTY_STEPS_COUNT; i > 0; i--) {
		_decreaseDutyCycle(rDutyStep, gDutyStep, bDutyStep);
		_delay(_DELAY_BASE_TICKS + i / 4);
	}

	BlinkerTask::MsgType msg;
	msg.token = msg::BlinkerEvent::WAIT;
	BlinkerTask::fifo_push(&msg);
}

void BlinkerTask::_setRedColor() {

	_pwm->setDutyCycle(_CHANNEL_G, 0);
	_pwm->setDutyCycle(_CHANNEL_B, 0);
	_pwm->setDutyCycle(_CHANNEL_R, _BLINKER_PERIOD_US - 1);
}

void BlinkerTask::_setGreenColor() {
	_pwm->setDutyCycle(_CHANNEL_R, 0);
	_pwm->setDutyCycle(_CHANNEL_B, 0);
	_pwm->setDutyCycle(_CHANNEL_G, _BLINKER_PERIOD_US - 1);
}

void BlinkerTask::_delay(uint32_t ticks) {
	Thread::Delay(ticks);
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

	while ((abs(rDutyStep - gDutyStep) < 10) &&
		   (abs(rDutyStep - bDutyStep) < 10) &&
		   (abs(gDutyStep - bDutyStep) < 10)) {
		rDutyStep = rand() % (_MAX_DUTY_STEP + 1);
		gDutyStep = rand() % (_MAX_DUTY_STEP + 1);
		bDutyStep = rand() % (_MAX_DUTY_STEP + 1);
	}
}

}
