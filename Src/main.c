#include "CACHE.h"
#include "TIM.h"
#include "UART.h"

#include <stdio.h>
#include <stdint.h>

int main(void)
{
	UART3_Init();
	CACHE_Init();

    while (1)
    {

    }
}
