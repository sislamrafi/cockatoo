#include "timer1.h"
// #include "../../protocols/usart/usart.h"
// #include "../stdlib/stdlibc.h"

static uint32_t TIM1_INTERRUPT_CALL_COUNT = 0;
static uint8_t TIM1_READY_TO_USE = 0;

void ConfigTimer1(void) {
  // 1. Enable Timer2 clock
  RCC->APB2ENR |= 1 << 0;

  // 2. Set the Prescalar
  TIM1->PSC = TIM1_PSC - 1;

  /*
      THE APB2 BUS CLOCK IS 180MHz
      SO EVERY TIMER DELAY IS 180MHz/180 = 1 microseconds
  */

  // 3. Set the Auto-Reload-Resister value. Set max value for 32 bits.
  TIM1->ARR = (uint32_t)TIM1_ARR;

  // update interrupt enable
  TIM1->DIER = 1 << 0;

  // Re-initialize the counter and generates an update of the registers.
  TIM1->EGR = 1 << 0;

  // 4. Enable the Timer, and wait for the update Flag to set
  TIM1->CR1 |= 1 << 0;
  while (!(TIM1->SR & (1 << 0)))
    ; // wait until the update flag is set

  __NVIC_EnableIRQ(TIM1_CC_IRQn);
  TIM1->SR = ~(1 << 0);

  TIM1->CNT = 0;

  TIM1_READY_TO_USE = 1;
}


void TIM1_CC_IRQHandler() {
  TIM1->SR = ~(1 << 0); // clear interrupt flag
  if (!TIM1_READY_TO_USE)
    return;
  TIM1_INTERRUPT_CALL_COUNT++;
  TIM1->CNT = 0;
  TIM1_ROUTINE();
}