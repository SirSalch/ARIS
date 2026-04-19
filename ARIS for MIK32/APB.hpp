#ifndef _APB_HPP_
#define _APB_HPP_

#include <stdint.h>


// Базовы адрес APB шины
#define APB_BASE 0x00050000

// Карта регистров APB шины
struct APB_Regs {
  uint32_t Reserved0;
  volatile uint32_t DIVIDER_MAIN;
  volatile uint32_t DIVIDER_PERIPHERY;
  uint32_t Reserved1[2];
  volatile uint32_t CLK_MAIN_SET;
  volatile uint32_t CLK_MAIN_CLEAR;
  volatile uint32_t CLK_PERIPHERY_SET;
  volatile uint32_t CLK_PERIPHERY_CLEAR;
};

// Шина APB
#define APB ((APB_Regs*)APB_BASE)


// Битовые маски
enum {
  // Маски тактирования периферии
  CLK_WATCH_DOG_TIMER = 1 << 0,
  CLK_UART_0          = 1 << 1,
  CLK_UART_1          = 1 << 2,
  CLK_TIM16_0         = 1 << 3,
  CLK_TIM16_1         = 1 << 4,
  CLK_TIM16_2         = 1 << 5,
  CLK_TIM32_1         = 1 << 6,
  CLK_TIM32_2         = 1 << 7,
  CLK_SPI_0           = 1 << 8,
  CLK_SPI_1           = 1 << 9,
  CLK_I2C_0           = 1 << 10,
  CLK_I2C_1           = 1 << 11,
  CLK_GPIO_0          = 1 << 12,
  CLK_GPIO_1          = 1 << 13,
  CLK_GPIO_2          = 1 << 14,
  CLK_ANALOG_BLOCK    = 1 << 15,
  CLK_GPIO_INTERRUPTS = 1 << 16,
};


namespace Apb {
  inline void setPeripheryClocking(const uint32_t clkMask, const bool state) {
    (state ? APB->CLK_PERIPHERY_SET : APB->CLK_PERIPHERY_CLEAR) = clkMask;
  }
};

#endif /* _APB_HPP_ */