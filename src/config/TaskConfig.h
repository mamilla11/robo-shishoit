#pragma once

#include <config/FreeRTOSConfig.h>
#include <cstdint>
#include <cstring>

namespace config {

namespace tasks {
static constexpr uint32_t MIN_TASK_STACK_SIZE = configMINIMAL_STACK_SIZE;
static constexpr uint32_t MIN_TASK_PRIORITY = 1;

struct BlinkerTask {
    static constexpr uint32_t STACK_SIZE = MIN_TASK_STACK_SIZE;
    static constexpr const char NAME[]   = "Blinker Task";
    static constexpr uint32_t PRIORITY   = MIN_TASK_PRIORITY;
    static constexpr uint32_t FIFO_SIZE  = 2;
};

struct TimeTask {
    static constexpr uint32_t STACK_SIZE = MIN_TASK_STACK_SIZE;
    static constexpr const char NAME[]   = "Time Task";
    static constexpr uint32_t PRIORITY   = MIN_TASK_PRIORITY;
    static constexpr uint32_t SLEEP_TIME = 1000;
};

struct DisplayTask {
    static constexpr uint32_t STACK_SIZE = MIN_TASK_STACK_SIZE;
    static constexpr const char NAME[]   = "Display Task";
    static constexpr uint32_t PRIORITY   = MIN_TASK_PRIORITY;
    static constexpr uint32_t SLEEP_TIME = 1;
};

struct LogicTask {
    static constexpr uint32_t STACK_SIZE = MIN_TASK_STACK_SIZE;
    static constexpr const char NAME[]   = "Logic Task";
    static constexpr uint32_t PRIORITY   = MIN_TASK_PRIORITY;
    static constexpr uint32_t FIFO_SIZE  = 2;
};

}

}
