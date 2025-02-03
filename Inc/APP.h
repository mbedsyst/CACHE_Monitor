#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>

#define CACHE_LINE_SIZE 	16
#define CACHE_SIZE_KB 		8
#define CACHE_LINES 		(CACHE_SIZE_KB * 1024 / CACHE_LINE_SIZE)

void ExhaustCache(void);

#endif
