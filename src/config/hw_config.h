#pragma once

#include <libopencm3/stm32/gpio.h>

namespace config {
static constexpr uint32_t SYSTEM_CORE_CLOCK = 72000000;
static constexpr uint32_t SYSTEM_CORE_CLOCK_DIV = 1000;

static constexpr uint32_t EYES_R_PORT = GPIOA;
static constexpr uint32_t EYES_R_PIN = GPIO15;

static constexpr uint32_t EYES_G_PORT = GPIOB;
static constexpr uint32_t EYES_G_PIN = GPIO3;

static constexpr uint32_t EYES_B_PORT = GPIOB;
static constexpr uint32_t EYES_B_PIN = GPIO10;

static constexpr uint32_t BLINKER_R_PORT = GPIOB;
static constexpr uint32_t BLINKER_R_PIN = GPIO4;

static constexpr uint32_t BLINKER_G_PORT = GPIOB;
static constexpr uint32_t BLINKER_G_PIN = GPIO5;

static constexpr uint32_t BLINKER_B_PORT = GPIOB;
static constexpr uint32_t BLINKER_B_PIN = GPIO0;
}


