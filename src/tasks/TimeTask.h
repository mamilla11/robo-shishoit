#pragma once

#include <thread.hpp>
#include <ticks.hpp>

#include <config/TaskConfig.h>

namespace tasks {

namespace rtos = cpp_freertos;

class TimeTask final : rtos::Thread {
public:
	TimeTask();
	~TimeTask() = default;

	void Run();
};

}
