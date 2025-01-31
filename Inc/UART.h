#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "stm32h5xx.h"

void UART3_Init(void);
void UART3_TxChar(char ch);
void UART3_TxString(char *str);
uint8_t UART3_RxChar(void);

#endif
