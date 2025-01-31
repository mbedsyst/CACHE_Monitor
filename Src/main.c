#include "UART.h"
#include "SYSTICK.h"
#include <stdio.h>

int main(void)
{
    UART3_Init();

    while (1)
    {
    	printf("Hello World\n\r");
    	delay_ms(1000);
    }
}
