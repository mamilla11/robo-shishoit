#pragma once

#include <thread.hpp>
#include <ticks.hpp>

#include <config/TaskConfig.h>
#include <hw/Display.h>

namespace tasks {

namespace rtos = cpp_freertos;

class DisplayTask final : rtos::Thread {
public:
	DisplayTask();
	~DisplayTask() = default;

	void Run();

	static void setChar(uint8_t char_i, uint8_t number, bool dotted = false);

private:
	static hw::Display _display;
};

}
