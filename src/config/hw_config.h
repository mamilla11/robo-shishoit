#pragma once

#include <libopencm3/stm32/gpio.h>

namespace config {
static constexpr uint32_t SYSTEM_CORE_CLOCK = 72000000;
static constexpr uint32_t SYSTEM_CORE_CLOCK_DIV = 1000;

static constexpr uint32_t EYES_R_PORT = GPIOA;
static constexpr uint16_t EYES_R_PIN = GPIO15;

static constexpr uint32_t EYES_G_PORT = GPIOB;
static constexpr uint16_t EYES_G_PIN = GPIO3;

static constexpr uint32_t EYES_B_PORT = GPIOB;
static constexpr uint16_t EYES_B_PIN = GPIO10;

static constexpr uint32_t BLINKER_R_PORT = GPIOB;
static constexpr uint16_t BLINKER_R_PIN = GPIO4;

static constexpr uint32_t BLINKER_G_PORT = GPIOB;
static constexpr uint16_t BLINKER_G_PIN = GPIO5;

static constexpr uint32_t BLINKER_B_PORT = GPIOB;
static constexpr uint16_t BLINKER_B_PIN = GPIO0;

static constexpr uint8_t CHAR_COUNT = 4;
static constexpr uint32_t CHAR_SEL_PORTS[CHAR_COUNT] = {
		GPIOB, GPIOB, GPIOC, GPIOB
};
static constexpr uint32_t CHAR_SEL_PINS[CHAR_COUNT] = {
		GPIO2, GPIO13, GPIO13, GPIO8
};

static constexpr uint32_t CHAR_SEG_PORT = GPIOA;

static void swj_disable() {
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON, 0);
}
}

