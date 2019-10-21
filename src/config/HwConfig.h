#pragma once

#include <cstdint>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/rtc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencmsis/core_cm3.h>

namespace config {

static constexpr uint32_t EYES_R_PORT = GPIOA;
static constexpr uint16_t EYES_R_PIN = GPIO15;

static constexpr uint32_t EYES_G_PORT = GPIOB;
static constexpr uint16_t EYES_G_PIN = GPIO3;

static constexpr uint32_t EYES_B_PORT = GPIOB;
static constexpr uint16_t EYES_B_PIN = GPIO10;

static constexpr uint32_t EYES_TIM = TIM2;

static constexpr uint32_t BLINKER_R_PORT = GPIOB;
static constexpr uint16_t BLINKER_R_PIN = GPIO4;

static constexpr uint32_t BLINKER_G_PORT = GPIOB;
static constexpr uint16_t BLINKER_G_PIN = GPIO5;

static constexpr uint32_t BLINKER_B_PORT = GPIOB;
static constexpr uint16_t BLINKER_B_PIN = GPIO0;

static constexpr uint32_t BLINKER_TIM = TIM3;

static constexpr uint32_t TOUCH_PORT = GPIOA;
static constexpr uint16_t TOUCH_PIN  = GPIO8;
static constexpr uint32_t TOUCH_NVIC = NVIC_EXTI9_5_IRQ;

static constexpr uint32_t LONG_PRESS_TIM = TIM1;
static constexpr uint32_t LONG_PRESS_TIM_PRESCALER = 0xFFFE;
static constexpr uint32_t LONG_PRESS_TIM_PERIOD = 2000;
static constexpr uint32_t LONG_PRESS_NVIC = NVIC_TIM1_UP_IRQ;
static constexpr uint32_t LONG_PRESS_NVIC_PRIO = 191 + 0x10;


static constexpr uint32_t BACKLIGHT_PORT = GPIOB;
static constexpr uint16_t BACKLIGHT_PIN = GPIO1;

static constexpr uint32_t HANDLED_PORT = GPIOB;
static constexpr uint16_t HANDLED_PIN = GPIO9;

static constexpr uint32_t BUTTON_LEFT_PORT = GPIOB;
static constexpr uint16_t BUTTON_LEFT_PIN = GPIO15;

static constexpr uint32_t BUTTON_RIGHT_PORT = GPIOB;
static constexpr uint16_t BUTTON_RIGHT_PIN = GPIO12;

static constexpr uint16_t BUTTON_LEFT_EXTI = EXTI15;
static constexpr uint16_t BUTTON_RIGHT_EXTI = EXTI12;

static constexpr uint32_t BUTTONS_NVIC = NVIC_EXTI15_10_IRQ;

static constexpr rcc_osc RTC_SOURCE = rcc_osc::RCC_LSE;
static constexpr uint32_t RTC_PRESCALER = 0x7FFF;

static constexpr uint32_t CHAR_1_SEL_PORT = GPIOB;
static constexpr uint32_t CHAR_2_SEL_PORT = GPIOB;
static constexpr uint32_t CHAR_3_SEL_PORT = GPIOC;
static constexpr uint32_t CHAR_4_SEL_PORT = GPIOB;

static constexpr uint16_t CHAR_1_SEL_PIN = GPIO2;
static constexpr uint16_t CHAR_2_SEL_PIN = GPIO13;
static constexpr uint16_t CHAR_3_SEL_PIN = GPIO13;
static constexpr uint16_t CHAR_4_SEL_PIN = GPIO8;

static constexpr uint32_t CHAR_SEG_PORT = GPIOA;

inline void SWJDisable() {
	uint32_t remap = AFIO_MAPR_TIM3_REMAP_PARTIAL_REMAP |
			         AFIO_MAPR_TIM2_REMAP_FULL_REMAP;
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON, remap);
}

}

