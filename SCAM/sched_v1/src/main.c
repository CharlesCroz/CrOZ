#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "sched.h"
#include "millis.h"

#define RED_FREQ_HZ 2
#define GREEN_FREQ_HZ 50

void led_red(void){
    DDRB |= (1 << PORTB5);
    uint32_t last_tick = 0;

    while(1){
        uint32_t tick = get_millis();
        if(tick >= last_tick + (500 / RED_FREQ_HZ)){
            last_tick += (500 / RED_FREQ_HZ);
            PORTB ^= (1 << PORTB5);
        }
    }
}

void led_green(void){
    DDRB |= (1 << PORTB4);
    uint32_t last_tick = get_millis();

    while(1){
        uint32_t tick = get_millis();
        if(tick >= last_tick + (500 / GREEN_FREQ_HZ)){
            last_tick += (500 / GREEN_FREQ_HZ);
            PORTB ^= (1 << PORTB4);
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
            .ms = 0,
            .stack_pointer = 0x700,
        },
        {
            .status = STATUS_INIT,
            .func = &led_green,
            .ms = 1,
            .stack_pointer = 0x500,
        },
        {
            .status = STATUS_INIT,
            .func = &led_red,
            .ms = 1,
            .stack_pointer = 0x600,
        }
    };
    const uint8_t processes_count = sizeof(processes)/sizeof(processes[0]);
    
    start_millis();
    start_scheduler(processes, processes_count);

    while(1) //infinite loop
        ;

    return 0;
}