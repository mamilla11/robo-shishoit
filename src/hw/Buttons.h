#pragma once

#include <config/HwConfig.h>

extern "C" void exti15_10_isr(void);

namespace hw {

class Buttons {
public:
	Buttons();
	~Buttons() = default;

	void notifyLeftButtonPressed();
	void notifyRightButtonPressed();

private:
	void _setup_gpio();
	void _setup_exti();
};

}

