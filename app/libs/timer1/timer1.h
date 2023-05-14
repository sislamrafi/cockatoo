#ifndef __TIMER_H__
#define __TIMER_H__

#include "../../main/board.h"

#define TIM1_CLOCK_SPEED 180000000U
#define TIM1_PSC 180U
#define TIM1_TICK_TIME (uint32_t)(TIM1_CLOCK_SPEED/TIM1_PSC)
#define TIM1_TICK_TIME_MS_DIV (uint32_t)((TIM1_TICK_TIME)/1000U)
#define TIM1_TICK_TIME_US_DIV (uint32_t)((TIM1_TICK_TIME)/1000000U)
#define TIM1_ARR (uint32_t)20000U // 20ms //max: 0xffffffff - 1

extern void TIM1_ROUTINE(void);
extern void TIM1_CC_IRQHandler(void);

#endif
