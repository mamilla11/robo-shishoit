#include "Eyes.h"

namespace hw {

Eyes::Eyes() {
	_pwmTimer = new hw::PWMTimer(config::EYES_TIM, _PERIOD_US);
	_pwmTimer->setupChannel(config::EYES_R_PORT, config::EYES_R_PIN, _CHANNEL_R);
	_pwmTimer->setupChannel(config::EYES_G_PORT, config::EYES_G_PIN, _CHANNEL_G);
	_pwmTimer->setupChannel(config::EYES_B_PORT, config::EYES_B_PIN, _CHANNEL_B);
	_pwmTimer->on();

	setColor(currentColor);
}

void Eyes::setColor(Color color) {
	switch (color) {
		case Color::RED:
			_rDuty = _intensity;
			_gDuty = _MAX_DUTY_CYCLE;
			_bDuty = _MAX_DUTY_CYCLE;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _MAX_DUTY_CYCLE);
			break;
		case Color::GREEN:
			_rDuty = _MAX_DUTY_CYCLE;
			_gDuty = _intensity;
			_bDuty = _MAX_DUTY_CYCLE;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _MAX_DUTY_CYCLE);
			break;
		case Color::BLUE:
			_rDuty = _MAX_DUTY_CYCLE;
			_gDuty = _MAX_DUTY_CYCLE;
			_bDuty = _intensity;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _intensity);
			break;
		case Color::MAGENTA:
			_rDuty = _intensity;
			_gDuty = _MAX_DUTY_CYCLE;
			_bDuty = _intensity;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _intensity);
			break;
		case Color::CYAN:
			_rDuty = _MAX_DUTY_CYCLE;
			_gDuty = _intensity;
			_bDuty = _intensity;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _MAX_DUTY_CYCLE);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _intensity);
			break;
		case Color::YELLOW:
			_rDuty = _intensity;
			_gDuty = _intensity;
			_bDuty = _MAX_DUTY_CYCLE;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _MAX_DUTY_CYCLE);
			break;
		case Color::WHITE:
			_rDuty = _intensity;
			_gDuty = _intensity;
			_bDuty = _intensity;

			_pwmTimer->setDutyCycle(_CHANNEL_R, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_G, _intensity);
			_pwmTimer->setDutyCycle(_CHANNEL_B, _intensity);
			break;
		default: break;
	}
}

void Eyes::setNextColor() {
	currentColor = (Color)((uint8_t)currentColor + 1);

	if (currentColor == Color::COUNT) {
		currentColor = Color::RED;
	}

	setColor(currentColor);
}

void Eyes::blink() {
	static bool enable = false;

	if (enable) {
		on();
	} else {
		off();
	}

	enable = !enable;
}

void Eyes::on() {
	_pwmTimer->setDutyCycle(_CHANNEL_R, _rDuty);
	_pwmTimer->setDutyCycle(_CHANNEL_G, _gDuty);
	_pwmTimer->setDutyCycle(_CHANNEL_B, _bDuty);
}
void Eyes::off() {
	_pwmTimer->setDutyCycle(_CHANNEL_R, _MAX_DUTY_CYCLE);
	_pwmTimer->setDutyCycle(_CHANNEL_G, _MAX_DUTY_CYCLE);
	_pwmTimer->setDutyCycle(_CHANNEL_B, _MAX_DUTY_CYCLE);
}


}




