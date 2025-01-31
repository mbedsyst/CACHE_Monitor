#include "UART.h"
#include <stdio.h>

int main(void)
{
    UART3_Init();

    while (1)
    {
    	printf("Hello World\n\r");
    	for(int i = 0; i < 20000; i++);
    }
}
