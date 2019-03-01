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

	LogicTask::MsgType msg;

    while (true) {
        Thread::Delay(delay);

        msg.token = tasks::msg::LogicEvent::UPDATE_TIME;
        LogicTask::fifo_push_from_isr(&msg);
    }
}

}
