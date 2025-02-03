#include "CACHE.h"
#include "TIM.h"
#include <stdio.h>

#define SYSTEM_CLOCK  32000000  // System clock is 32MHz

void TIM2_Init(void)
{
    RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
    // Scale TIM2 Clock to 10 KHz
    TIM2->PSC = (SYSTEM_CLOCK / 10000) - 1;
    // Run the counter for 10000 cycles
    TIM2->ARR = 19999;
    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);
    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        CACHE_UpdateMonitor();
    }
}
