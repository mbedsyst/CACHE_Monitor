#include "UART.h"

/* USART3 TX - PD8
 * USART3 RX - PD9
 */

#define UART_BAUDRATE	115200
#define SYS_FREQ		32000000
#define APB1_CLK		SYS_FREQ

static uint16_t Compute_UART_Baud(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void UART3_SetBaudRate(uint32_t periph_clk, uint32_t baudrate)
{
	USART3->BRR = Compute_UART_Baud(periph_clk,baudrate);
}

void UART3_Init(void)
{
    /* Enable clock access to GPIOA and UART2 */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;

    /* Set PD8 and PD9 to alternate function mode */
    GPIOD->MODER &= ~((3U << 16) | (3U << 18));
    GPIOD->MODER |= (2U << 16) | (2U << 18);

    /* Set Alternate Function type to USART3 (AF7) */
    GPIOD->AFR[1] |= (7U << 0) | (7U << 4);

    // Disable USART3 Peripheral
    USART3->CR1 &= ~(1<<0);

    /* Configure Baud Rate */
    UART3_SetBaudRate(APB1_CLK,UART_BAUDRATE); // For 32 MHz and 115200 baud

    /* Enable TX, RX, and UART */
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UART3_TxChar(char ch)
{
	/*Wait for Transmit Data Register to be empty*/
	while(!(USART3->ISR & USART_ISR_TXE));
	/*Write to the Transmit Data Register*/
	USART3->TDR = (ch & 0xFF);
}

void UART3_TxString(char *str)
{
	while(*str)
	{
		UART3_TxChar(*str++);
	}
}

uint8_t UART3_RxChar(void)
{
    while(!(USART3->ISR & USART_ISR_RXNE)); // Wait for RXNE flag (data received)
    return (uint8_t)(USART3->RDR & 0xFF); // Return the received data
}

int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        UART3_TxChar(ptr[i]);  // Transmit each character via UART2
    }
    return len;  // Return the number of characters written
}

int _read(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        ptr[i] = UART3_RxChar();  // Read each character via UART2
        if (ptr[i] == '\r')      // Handle Enter key as a newline
        {
            ptr[i] = '\n';       // Convert '\r' to '\n' for standard behavior
            return i + 1;        // Return number of characters read
        }
    }
    return len;  // Return number of characters read
}
