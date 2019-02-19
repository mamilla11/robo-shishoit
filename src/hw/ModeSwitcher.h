#pragma once

#include <config/HwConfig.h>

extern "C" void exti9_5_isr(void);

namespace hw {

class ModeSwitcher {
public:
	enum class Mode : uint8_t {
		IDLE = 0,
		EYES_SETUP,
		TIME_SETUP,

		COUNT
	};

	Mode mode = Mode::IDLE;

	ModeSwitcher();
	~ModeSwitcher() = default;

	void toNextState();

private:
	void _setup_gpio();
	void _setup_exti();
};

}
