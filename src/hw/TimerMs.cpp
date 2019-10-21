#include "TimerMs.h"

namespace hw {

TimerMs::TimerMs(TimerMode mode, uint32_t period_ms)
{
	_mode = mode;
	_saved_ms = get_counter_ms();
	_period_ms = period_ms;

	switch (_mode)
	{
		case TimerMode::CYCLE:
			_is_active = true;
			break;
		case TimerMode::ONE_SHOT:
			_is_active = false;
			break;
	}
}

bool TimerMs::timeout()
{
	if (_is_active && ((get_counter_ms() - _saved_ms) >= _period_ms)) {
		switch (_mode)
		{
			case TimerMode::CYCLE:
				_saved_ms = get_counter_ms();
				return true;
			case TimerMode::ONE_SHOT:
				return true;
		}
	}

	return false;
}

bool TimerMs::start()
{
	if(_mode == TimerMode::CYCLE)
		return false;
	_saved_ms = get_counter_ms();
	_is_active = true;
	return true;
}

bool TimerMs::stop()
{
	if(_mode == TimerMode::CYCLE)
		return false;
	_is_active = false;
	return true;
}

}
