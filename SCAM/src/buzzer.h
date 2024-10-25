#include <avr/io.h>
#include <stdint.h>

#ifndef SCAM_BUZZER
#define SCAM_BUZZER

#define _TONE_CLI()                     \
    asm volatile (                      \
		"push	r0				\n\t"   \
		"in		r0, __SREG__	\n\t"   \
		"cli					\n\t"   \
		"push	r0				\n\t"   \
    );

#define _TONE_CLI_INV()                 \
    asm volatile (                      \
		"pop	r0				\n\t"   \
		"out 	__SREG__, r0	\n\t"   \
		"pop	r0				\n\t"   \
    );


volatile uint8_t _tone_port;
volatile uint8_t _tone_pin;
volatile uint16_t _tone_changes_count;

void tone_start();
void tone_stop();
void tone_attach();
uint8_t tone_set(uint16_t freq, uint16_t time_millis);
void _tone_switch();

void tone_attach(){
    DDRB |= (1 << PORTB5);
}

uint8_t tone_set(uint16_t freq, uint16_t time_millis){
    uint32_t n_cycles = (F_CPU / freq);
    uint32_t n_changes = time_millis * freq / 500;
    uint8_t prescaler = 2;
    
    _TONE_CLI()

    /* Freq boundaries */
    if(freq < 30 || freq > 20000)
        return 0;
    
    if(n_cycles < 2048){
        n_cycles = n_cycles / 8;
    }else if(n_cycles < 16384){
        prescaler = 3;
        n_cycles = n_cycles / 64;
    }else if(n_cycles < 65536){
        prescaler = 4;
        n_cycles = n_cycles / 256;
    }else{
        prescaler = 5;
        n_cycles = n_cycles / 1024;
    }

    if(n_cycles > 255)
        return 0;

    /* Attach interrupt */
    *((uint16_t *) 0x1C) = (uint16_t)&_tone_switch;

    /* Clear OC0A on compare (set elsewhere) */
    TCCR0A &= ~(1 << COM0A0);
    TCCR0A &= ~(1 << COM0A1);

    /* Set timer mode as CTC (clear timer on compare match) */
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0A &= ~(1 << WGM02);

    /* Prescaler */
    TCCR0B = (TCCR0B & ~0x3) | (prescaler & 0x3);

    /* Set COMPA value */
    OCR0A = (uint8_t) n_cycles;
    _tone_changes_count = n_changes;

    _TONE_CLI_INV()

    return 1;
}

void tone_start(){
    /* Start TIMER0 COMPA */
    TCCR0A |= (1 << COM0A0);
    TCCR0A |= (1 << COM0A1);
    
    /* Set interrupt */
    TIMSK0 |= (1 << OCIE0A);
    sei();
}

void tone_stop(){
    /* Stop TIMER0 COMPA */
    TCCR0A &= ~(1 << COM0A0);
    TCCR0A &= ~(1 << COM0A1);
}

void _tone_switch(){
    _TONE_CLI()
    
    if(!_tone_changes_count)
        tone_stop();
    PORTB ^= (1 << PORTB5);
    _tone_changes_count--;

    _TONE_CLI_INV()
}

#endif // SCAM_BUZZER