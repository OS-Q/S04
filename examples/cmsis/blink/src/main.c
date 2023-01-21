#ifdef STM32L0
#include "stm32l0xx.h"
#define LEDPORT (GPIOB)
#define LED1 (3)
#define ENABLE_GPIO_CLOCK (RCC->IOPENR |= RCC_IOPENR_GPIOBEN)
#define _MODER    MODER
#define GPIOMODER (GPIO_MODER_MODE3_0)
#elif STM32F0
#include "stm32f0xx.h"
#define LEDPORT (GPIOC)
#define LED1 (8)
#define ENABLE_GPIO_CLOCK (RCC->AHBENR |= RCC_AHBENR_GPIOCEN)
#define _MODER    MODER
#define GPIOMODER (GPIO_MODER_MODER8_0)
#elif STM32G0
#include "stm32g0xx.h"
#define LEDPORT      (GPIOB)
#define LED1         (7)
#define ENABLE_GPIO_CLOCK  (RCC->IOPENR |= RCC_IOPENR_GPIOBEN)
#define _MODER       MODER
#define GPIOMODER    (GPIO_MODER_MODE7_0)
#endif


void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=5000;
      while (x-- > 0)
         __asm("nop");
   }
}

//Alternates blue and green LEDs quickly
int main(void)
{
   ENABLE_GPIO_CLOCK;              // enable the clock to GPIO
   LEDPORT->_MODER |= GPIOMODER;   // set pins to be general purpose output
   for (;;) {
   ms_delay(500);
   LEDPORT->ODR ^= (1<<LED1);  // toggle diodes
   }

   return 0;
}
