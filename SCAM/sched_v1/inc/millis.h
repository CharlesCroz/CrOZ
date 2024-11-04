#ifndef __SCAM_MILLIS
#define __SCAM_MILLIS

#include <stdint.h>

void start_millis();

volatile uint32_t get_millis();

#endif // __SCAM_MILLIS