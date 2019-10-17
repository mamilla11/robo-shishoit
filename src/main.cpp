#include <thread.hpp>
#include <ticks.hpp>
#include <critical.hpp>
#include <queue.hpp>

#include <config/FreeRTOSConfig.h>
#include <config/HwConfig.h>
#include <config/Clock.hpp>
#include <hw/SystemState.h>

#include <tasks/BlinkerTask.h>
#include <tasks/LogicTask.h>
#include <tasks/TimeTask.h>
#include <tasks/DisplayTask.h>

namespace rtos = cpp_freertos;

extern "C" {
    void* __dso_handle;
    void* _fini;
}

int main(void)
{
	config::ClockInit();
	config::SystickInit();
	config::SWJDisable();

	__disable_irq();

	auto logicTask = new tasks::LogicTask();
//	auto blinkerTask = new tasks::BlinkerTask();
//	auto timeTask = new tasks::TimeTask();
//	auto displayTask = new tasks::DisplayTask();


	while(true) {
		logicTask->process();
	}
	return 0;
}

void* malloc(size_t size)
{
    return pvPortMalloc(size);
}

void* calloc(size_t num, size_t size)
{
    return pvPortMalloc(num * size);
}

void free(void* ptr)
{
    return vPortFree(ptr);
}

void* operator new(size_t sz)
{
    return pvPortMalloc(sz);
}

void* operator new[](size_t sz)
{
    return pvPortMalloc(sz);
}

void operator delete(void* p)
{
    vPortFree(p);
}

void operator delete[](void* p)
{
    vPortFree(p);
}

extern "C" {
void vAssertCalled(const char* pcFile, unsigned long ulLine)
{
    rtos::CriticalSection::Enter();
    {
        while(true)
        {
            portNOP();
        }
    }
    rtos::CriticalSection::Exit();
}

void vApplicationMallocFailedHook()
{
    rtos::CriticalSection::Enter();
    {
        while(true)
        {
            portNOP();
        }
    }
    rtos::CriticalSection::Exit();
}

void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   char* pcTaskName)
{
    rtos::CriticalSection::Enter();
    {
        while (true)
        {
            portNOP();
        }
    }
    rtos::CriticalSection::Exit();
}
}
