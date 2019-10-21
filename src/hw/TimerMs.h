#pragma once

#include <stdint.h>
#include "Systick.h"

namespace hw {
class TimerMs
{
public:
	enum class TimerMode : uint8_t {
		CYCLE,
		ONE_SHOT
	};

	TimerMs(TimerMode mode, uint32_t period_ms);
	bool timeout();
	bool start();
	bool stop();

private:
	uint32_t _saved_ms;
	uint32_t _period_ms;
	TimerMode _mode;
	bool _is_active;
};
}

