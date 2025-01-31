#include "SYSTICK.h"

void delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick->LOAD = 31999;
	SysTick->VAL |= 0x00FFFFFF;
	SysTick->CTRL |= (1<<0) | (1<<2);

	for(i = 0; i < ms; i++)
	{
		while(!(SysTick->CTRL & (1<<16)));
	}
	SysTick->CTRL &= ~(1U<<0) ;
}
