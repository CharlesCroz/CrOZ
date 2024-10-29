#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "sched.h"
#include "millis.h"

#define RED_FREQ_HZ 5
#define GREEN_FREQ_HZ 3

void led_red(void){
    DDRB |= (1 << PORTB5);
    uint16_t last_tick = 0;

    while(1){
        uint16_t tick = get_millis();
        if(tick >= last_tick + (500 / RED_FREQ_HZ)){
            last_tick += (500 / RED_FREQ_HZ);
            PORTB ^= (1 << PORTB5);
        }
    }
}

void led_green(void){
    DDRB |= (1 << PORTB4);
    uint16_t last_tick = 0;

    while(1){
        uint16_t tick = get_millis();
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
            .ms = 1,
            .stack_pointer = 0x700,
        },
        {
            .status = STATUS_OFF,
            .func = &led_green,
            .ms = 20,
            .stack_pointer = 0x500,
        },
        {
            .status = STATUS_INIT,
            .func = &led_red,
            .ms = 250,
            .stack_pointer = 0x600,
        }
    };
    const uint8_t processes_count = sizeof(processes)/sizeof(processes[0]);
    
    start_millis();
    // start_scheduler(processes, processes_count);
    led_red();

    while(1) //infinite loop
        ;

    return 0;
}