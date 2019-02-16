#include "counter.h"
#include <hw/systick.h>

namespace hw {
Counter::Counter(Mode mode, uint32_t period_ms)
{
	_mode = mode;
	_saved_ms = systick::get_counter_ms();
	_period_ms = period_ms;

	switch (_mode)
	{
		case Mode::CYCLE:
			_is_active = true;
			break;
		case Mode::ONE_SHOT:
			_is_active = false;
			break;
	}
}

bool Counter::timeout()
{
	if (_is_active && ((systick::get_counter_ms() - _saved_ms) >= _period_ms)) {
		switch (_mode)
		{
			case Mode::CYCLE:
				_saved_ms = systick::get_counter_ms();
				return true;
			case Mode::ONE_SHOT:
				return true;
		}
	}

	return false;
}

bool Counter::start()
{
	if(_mode == Mode::CYCLE)
		return false;
	_saved_ms = systick::get_counter_ms();
	_is_active = true;
	return true;
}

bool Counter::stop()
{
	if(_mode == Mode::CYCLE)
		return false;
	_is_active = false;
	return true;
}
}



