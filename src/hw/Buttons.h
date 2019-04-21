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

	struct ll_config {
		uint32_t timer;
		uint16_t timerPrescaler;
		uint16_t timerPeriod;
		uint32_t timerNvic;
		uint32_t timerNvicPrio;
		uint32_t leftBtnPort;
		uint16_t leftBtnPin;
		uint16_t leftBtnExti;
		uint32_t leftBtnNvic;
		uint32_t rightBtnPort;
		uint16_t rightBtnPin;
		uint16_t rightBtnExti;
		uint32_t rightBtnNvic;
	};

	ll_config cfg;

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

