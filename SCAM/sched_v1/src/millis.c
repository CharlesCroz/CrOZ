#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sched.h"

/* Global variable for time keeping */
volatile uint32_t __sched_millis = 0;

/* Handler */
ISR(TIMER0_COMPA_vect){
    /* Upgrade counter */
    ++__sched_millis;
}

volatile uint32_t get_millis(){
	uint32_t res;
    cli();
    res = __sched_millis;
    sei();
    return res;
}

void start_millis(){
    cli();

    /* Configure Timer 0 */
    /* Prescaler 64, f_CPU = 16MHz */
    /* TCNT LSB = 1/250 ms */
    /* OCR0A == 250 <=> Interruption toutes les ms */
    TCCR0A = 0b00000010;
    TCCR0B = 0b00000011;
    TCNT0  = 0;
    OCR0A  = 250;
    TIMSK0 = 0b00000010;

	sei();
}
