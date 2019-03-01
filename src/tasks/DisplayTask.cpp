#include "DisplayTask.h"

namespace tasks {

hw::Display DisplayTask::_display;

DisplayTask::DisplayTask() :
		Thread(config::tasks::DisplayTask::NAME,
			   config::tasks::DisplayTask::STACK_SIZE,
			   config::tasks::DisplayTask::PRIORITY)
{
	_display = hw::Display();
	this->Start();
}

void DisplayTask::Run()
{
	TickType_t delay =
			rtos::Ticks::MsToTicks(config::tasks::DisplayTask::SLEEP_TIME);

    while (true) {
        Thread::Delay(delay);
        _display.setNextChar();
    }
}

void DisplayTask::setChar(uint8_t char_i, uint8_t number, bool dotted) {
	_display.setCharValue(char_i, number, dotted);
}

}
