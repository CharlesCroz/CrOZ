#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sched.h"

/* Global (shush) variables for processes handling in interrupts*/
volatile uint16_t __sched_millis = 0;

/* Handler */
ISR(TIMER0_COMPA_vect, ISR_NAKED){
    /* Stop current */
    ++__sched_millis;
	reti();
}

uint16_t get_millis(){
	return __sched_millis;
}

void start_millis(){
    cli();

    /* Configure Timer 0 */
    /* Prescaler 64, f_CPU = 16MHz */
    /* TCNT LSB = 1/250 ms */
    /* OCR0A == 125 <=> Interruption toutes les ms */
    TCCR0A = 0b00000010;
    TCCR0B = 0b00000011;
    TCNT0  = 0;
    OCR0A  = 250;
    TIMSK0 = 0b00000010;

	sei();
}
