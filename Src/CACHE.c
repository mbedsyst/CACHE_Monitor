#include <CACHE.h>
#include <stdio.h>

static void ICACHE_Init(void)
{
    // Disable ICACHE before configuration
    ICACHE->CR &= ~ICACHE_CR_EN;
    // Invalidate the cache
    ICACHE->CR |= ICACHE_CR_CACHEINV;
    while (ICACHE->SR & ICACHE_SR_BUSYF); // Wait until invalidation completes
    // Enable HIT/MISS monitoring
    ICACHE->CR |= ICACHE_CR_MISSMEN | ICACHE_CR_HITMEN;
    // Reset HIT/MISS counters
    ICACHE->CR &= ~(ICACHE_CR_MISSMRST | ICACHE_CR_HITMRST);
    // Enable ICACHE
    ICACHE->CR |= ICACHE_CR_EN;
}

void CACHE_Init(void)
{
	ICACHE_Init();
}

static void CACHE_ClearMonitor(void)
{
	printf("\033[2J\033[H");
}

static void CACHE_PrintBanner(void)
{
	printf("\n\r");
	printf(" ██████  █████   ██████ ██   ██ ███████     ███    ███  ██████  ███    ██ ██ ████████  ██████  ██████  \n\r");
	printf("██      ██   ██ ██      ██   ██ ██          ████  ████ ██    ██ ████   ██ ██    ██    ██    ██ ██   ██ \n\r");
	printf("██      ███████ ██      ███████ █████       ██ ████ ██ ██    ██ ██ ██  ██ ██    ██    ██    ██ ██████  \n\r");
	printf("██      ██   ██ ██      ██   ██ ██          ██  ██  ██ ██    ██ ██  ██ ██ ██    ██    ██    ██ ██   ██ \n\r");
	printf(" ██████ ██   ██  ██████ ██   ██ ███████     ██      ██  ██████  ██   ████ ██    ██     ██████  ██   ██ \n\r");
	printf("\n\r");
}

void CACHE_UpdateMonitor(void)
{
	CACHE_ClearMonitor();
	CACHE_PrintBanner();
	printf("\n\n\r");
	printf("█ ICACHE HIT  Counter : %lu\n\r", ICACHE->HMONR);
    printf("\n\r");
    printf("█ ICACHE MISS Counter : %lu\n\r", ICACHE->MMONR);
    printf("\n\r");

}
