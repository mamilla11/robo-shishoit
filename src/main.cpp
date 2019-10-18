#include <config/HwConfig.h>
#include <config/Clock.hpp>

#include <tasks/BlinkerTask.h>
#include <tasks/LogicTask.h>

extern "C" {
    void* __dso_handle;
    void* _fini;
}

int main(void)
{
	config::ClockInit();
	config::SystickInit();
	config::SWJDisable();

	auto logicTask = new tasks::LogicTask();
//	auto blinkerTask = new tasks::BlinkerTask();

	while(true) {
		logicTask->process();
	}
	return 0;
}
