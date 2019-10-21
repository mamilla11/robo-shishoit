#pragma once

#include <config/HwConfig.h>

namespace hw {

class Buttons {
public:
	Buttons();
	~Buttons() = default;

	struct ll_config {
		uint32_t leftBtnPort;
		uint16_t leftBtnPin;
		uint32_t rightBtnPort;
		uint16_t rightBtnPin;
	};

	ll_config cfg;

	bool isLeftButtonPressed();
	bool isRightButtonPressed();

private:
	void _setupGpio();
};

}

