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
        uint16_t k = -1;
        while(--k){
            uint8_t l = 20;
            while(--l)
                ;
        }
    }
}

void led_green(void){
    DDRB |= (1 << PORTB4);

    while(1){
        PORTB ^= (1 << PORTB4);
        uint16_t k = -1;
        while(--k){
            uint8_t l = 40;
            while(--l)
                ;
        }
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
            .ms = 20,
            .stack_pointer = 0x700,
        },
        {
            .status = STATUS_INIT,
            .func = &led_green,
            .ms = 20,
            .stack_pointer = 0x500,
        },
        {
            .status = STATUS_INIT,
            .func = &led_red,
            .ms = 20,
            .stack_pointer = 0x600,
        }
    };
    const uint8_t processes_count = sizeof(processes)/sizeof(processes[0]);
    
    start_scheduler(processes, processes_count);

    while(1) //infinite loop
        ;

    return 0;
}