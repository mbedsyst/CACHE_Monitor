#include "CACHE.h"
#include "TIM.h"
#include "UART.h"

#include <stdio.h>
#include <stdint.h>

#define NUM_FUNCTIONS 5
#define LOOP_COUNT    100000

// Function prototypes
void func1(void);
void func2(void);
void func3(void);
void func4(void);
void func5(void);

// Function pointer array to introduce randomness
void (*func_array[NUM_FUNCTIONS])(void) = {func1, func2, func3, func4, func5};

// ICACHE-Intensive Application
void run_icache_intensive_task(void)
{
    for (volatile int i = 0; i < LOOP_COUNT; i++)
    {
        // Randomly call different functions
        func_array[i % NUM_FUNCTIONS]();
    }
}

// Simple functions that will be frequently called
void func1(void) { asm volatile("nop"); }
void func2(void) { asm volatile("nop"); }
void func3(void) { asm volatile("nop"); }
void func4(void) { asm volatile("nop"); }
void func5(void) { asm volatile("nop"); }

int main(void)
{
	UART3_Init();
    ICACHE_Init();

    while (1)
    {
        run_icache_intensive_task();  // ICACHE-heavy workload
        ICACHE_UpdateMonitor();             // Print HIT/MISS counters
    }

    return 0;
}
