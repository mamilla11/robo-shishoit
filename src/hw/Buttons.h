#pragma once

#include <config/HwConfig.h>

extern "C" void exti15_10_isr(void);
extern "C" void tim1_up_isr(void);

namespace hw {

class Buttons {
public:
	Buttons();
	~Buttons() = default;

	enum class Notification {
		LEFT_PRESSED,
		RIGHT_PRESSED,
		LEFT_LONG_PRESS
	};

	bool isLeftButtonPressed();
	bool isRightButtonPressed();

	void leftButtonPressedHandler();
	void rightButtonPressedHandler();
	void longPressDetectedHandler();

private:
	bool _longPressDetected = false;

	void _setupGpio();
	void _setupExti();
	void _setupTimer();

	void _notifyLogicTask(Notification notification);
};

}

