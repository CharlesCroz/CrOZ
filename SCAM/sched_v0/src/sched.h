
#ifndef SCAM_BUZZER
#define SCAM_BUZZER

#include <avr/io.h>
#include <stdint.h>

#define STATUS_OFF 0
#define STATUS_RUNNING 1
#define STATUS_INIT 2

struct running_process {
    volatile uint8_t status;
    volatile uint8_t ms;
    volatile uint16_t heap_addr;
    void (*func)(void);
};


void start_scheduler(volatile struct running_process processes[], uint8_t count);


#endif // SCAM_BUZZER