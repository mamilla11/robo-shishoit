#include <hw/PWMTimer.h>

namespace hw {

PWMTimer::PWMTimer(uint32_t timer, uint32_t period) :
				 _timer(timer), _period(period) {

	_setupTimer();
}

void PWMTimer::setupChannel(uint32_t port, uint16_t pin, Channel channel) {
	gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, pin);
	gpio_set(port, pin);

	tim_oc_id _channel = static_cast<tim_oc_id>(channel);

	timer_enable_oc_output(_timer, _channel);
	timer_set_oc_mode(_timer, _channel, tim_oc_mode::TIM_OCM_PWM1);
	timer_set_oc_polarity_low(_timer, _channel);
	timer_enable_oc_preload(_timer, _channel);
}

void PWMTimer::setDutyCycle(Channel channel, uint16_t value) {
	timer_set_oc_value(_timer, static_cast<tim_oc_id>(channel), value);
}

void PWMTimer::increaseDutyCycle(Channel channel, uint16_t value) {
	uint16_t duty = getDutyCycle(channel);
	(duty + value) >= _period ? duty = _period - 1 : duty += value;
	setDutyCycle(channel, duty);
}

void PWMTimer::decreaseDutyCycle(Channel channel, uint16_t value) {
	uint16_t duty = getDutyCycle(channel);
	(duty - value) <= 0 ? duty = 0 : duty -= value;
	setDutyCycle(channel, duty);
}

uint16_t PWMTimer::getDutyCycle(Channel channel)
{
	switch (channel)
	{
	case Channel::CH1:
		return TIM_CCR1(_timer);
	case Channel::CH2:
		return TIM_CCR2(_timer);
	case Channel::CH3:
		return TIM_CCR3(_timer);
	case Channel::CH4:
		return TIM_CCR4(_timer);
	}

	return 0;
}

void PWMTimer::on() {
	timer_set_counter(_timer, 0);
	timer_enable_counter(_timer);
}

void PWMTimer::off() {
	timer_disable_counter(_timer);
}

void PWMTimer::_setupTimer() {
	timer_set_mode(_timer, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(_timer, 71);
	timer_set_period(_timer, _period);
}

}
