#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "sched.h"

void led_red(void){
    DDRB |= (1 << PORTB5);

    while(1){
        PORTB ^= (1 << PORTB5);
        _delay_ms(250);
    }
}

void led_green(void){
    DDRB |= (1 << PORTB4);

    while(1){
        PORTB ^= (1 << PORTB4);
        _delay_ms(500);
    }
}

void idle_proc(void){
    while(1);
}

int main(void)
{
    volatile struct running_process processes[] = {
        {
            .status = STATUS_INIT,
            .func = &idle_proc,
            .ms = 1,
            .heap_addr = 0x700,
        },
        {
            .status = STATUS_INIT,
            .func = &led_red,
            .ms = 20,
            .heap_addr = 0x700,
        },
        {
            .status = STATUS_INIT,
            .func = &led_green,
            .ms = 20,
            .heap_addr = 0x600,
        }
    };
    const uint8_t processes_count = sizeof(processes)/sizeof(processes[0]);
    
    start_scheduler(processes, processes_count);

    while(1) //infinite loop
        ;

    return 0;
}