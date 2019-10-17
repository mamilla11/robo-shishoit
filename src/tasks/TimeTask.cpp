#include <hw/SystemState.h>
#include "TimeTask.h"
#include "LogicTask.h"

namespace tasks {

TimeTask::TimeTask() :
		Thread(config::tasks::TimeTask::NAME,
			   config::tasks::TimeTask::STACK_SIZE,
			   config::tasks::TimeTask::PRIORITY)
{
	this->Start();
}

void TimeTask::Run()
{
	TickType_t delay =
			rtos::Ticks::MsToTicks(config::tasks::TimeTask::SLEEP_TIME);

    while (true) {
        Thread::Delay(delay);
        SystemState::pushEvent(SystemState::Event::UPDATE_TIME);
    }
}

}
