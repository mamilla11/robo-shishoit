#include <thread.hpp>
#include <ticks.hpp>
#include <critical.hpp>
#include <queue.hpp>

#include <config/FreeRTOSConfig.h>
#include <config/HwConfig.h>
#include <config/Clock.hpp>

#include <tasks/BlinkerTask.h>

#include <hw/ModeSwitcher.h>
#include <hw/Backlight.hpp>
#include <hw/Buttons.h>

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

	hw::ModeSwitcher *switcher = new hw::ModeSwitcher();
	hw::Backlight *backlight = new hw::Backlight();
	hw::Buttons *buttons = new hw::Buttons();
	auto blinkerTask = new tasks::BlinkerTask();

	rtos::Thread::StartScheduler();

	while(true);
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
