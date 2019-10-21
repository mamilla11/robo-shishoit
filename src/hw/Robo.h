#pragma once

#include <config/HwConfig.h>

namespace hw {

class Robo {
public:
	Robo();
	~Robo() = default;

	void toggleBacklight();
	void toggleHandLed();
	bool isLeftButtonPressed();
	bool isRightButtonPressed();
	bool isTouchPressed();

private:
	void _setupGpio();
};

}
