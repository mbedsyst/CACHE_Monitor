#include "CACHE.h"
#include "TIM.h"
#include <stdio.h>

#define SYS_CLOCK_HZ  32000000  // System clock is 32MHz

void TIM2_Init(void)
{
    // Enable TIM2 Clock
    RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;

    // Configure TIM2: Set prescaler and ARR for 1s interval
    TIM2->PSC = (SYS_CLOCK_HZ / 10000) - 1;  // Divide clock to 10kHz (PSC = 3199)
    TIM2->ARR = 19999;  // 10kHz / 10000 = 1Hz (1 second)

    // Enable update interrupt
    TIM2->DIER |= TIM_DIER_UIE;

    // Enable TIM2 interrupt in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);

    // Start the timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

// TIM2 Interrupt Handler
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    { // Check update interrupt flag
        TIM2->SR &= ~TIM_SR_UIF; // Clear the flag
        CACHE_UpdateMonitor();
    }
}
