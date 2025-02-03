#include "APP.h"

volatile uint8_t data[CACHE_LINES * CACHE_LINE_SIZE];

void ExhaustCache(void)
{
    volatile uint8_t temp;
    uint32_t i, j;
    for (i = 0; i < CACHE_LINES; i++)
    {
        for (j = 0; j < CACHE_LINE_SIZE; j++)
        {
            temp = data[i * CACHE_LINE_SIZE + j];
            temp++;
        }
    }
}
