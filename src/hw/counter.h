#pragma once

#include "stdint.h"

namespace hw {
class Counter {
public:
	enum class Mode : uint8_t {
		CYCLE,
		ONE_SHOT
	};

	Counter(Mode mode, uint32_t period_ms);
	~Counter() = default;

	bool timeout();
	bool start();
	bool stop();

private:
	uint32_t _saved_ms;
	uint32_t _period_ms;
	Mode _mode;
	bool _is_active;
};
}
