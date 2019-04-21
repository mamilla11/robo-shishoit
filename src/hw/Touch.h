#pragma once

#include <config/HwConfig.h>

extern "C" void exti9_5_isr(void);

namespace hw {

class Touch {
public:
	Touch();
	~Touch() = default;

	void notifyLogicTask();

private:
	void _setup_gpio();
	void _setup_exti();
};

}
