#include <thread.hpp>
#include <ticks.hpp>
#include <critical.hpp>
#include <queue.hpp>

#include <libopencmsis/core_cm3.h>

#include <config/FreeRTOSConfig.h>
#include <config/HwConfig.h>
#include <config/Clock.hpp>

#include <tasks/BlinkerTask.h>

#include <hw/counter.h>
#include <hw/rgb.h>
#include <hw/indicators.h>

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

	auto blinkerTask = new tasks::BlinkerTask();

	rtos::Thread::StartScheduler();

	while(true);
	return 0;

//	hw::Rgb *eyes = new hw::Rgb(config::EYES_R_PORT, config::EYES_R_PIN,
//						   config::EYES_G_PORT, config::EYES_G_PIN,
//			               config::EYES_B_PORT, config::EYES_B_PIN);
//	eyes->off();
//
//	hw::Indicators indicators = hw::Indicators(config::CHAR_SEL_PORTS,
//											   config::CHAR_SEL_PINS,
//											   config::CHAR_SEG_PORT);
//
//	uint8_t indicatorsValue = 0;
//	indicators.set_number(indicatorsValue);
//
//	hw::Counter timer1s = hw::Counter(hw::Counter::Mode::CYCLE, 1000);
//	hw::Counter timer1ms = hw::Counter(hw::Counter::Mode::CYCLE, 1);
//
//	while(1) {
//		if (timer1s.timeout()) {
//			blinker->set_next_color();
//			eyes->set_next_color();
//			if (++indicatorsValue == 10) {
//				indicatorsValue = 0;
//			}
//			indicators.set_number(indicatorsValue);
//		}
//
//		if (timer1ms.timeout()) {
//			indicators.set_next_indicator();
//		}
//	}
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
