#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sched.h"

#define __SCHED_SAVE_CONTEXT()          \
    asm volatile (                      \
		"push	r0				\n\t"   \
		"in		r0, __SREG__	\n\t"   \
		"cli					\n\t"   \
		"push	r0				\n\t"	\
		"push	r1				\n\t"	\
		"push	r2				\n\t"	\
		"push	r3				\n\t"	\
		"push	r4				\n\t"	\
		"push	r5				\n\t"	\
		"push	r6				\n\t"	\
		"push	r7				\n\t"	\
		"push	r8				\n\t"	\
		"push	r9				\n\t"	\
		"push	r10				\n\t"	\
		"push	r11				\n\t"	\
		"push	r12				\n\t"	\
		"push	r13				\n\t"	\
		"push	r14				\n\t"	\
		"push	r15				\n\t"	\
		"push	r16				\n\t"	\
		"push	r17				\n\t"	\
		"push	r18				\n\t"	\
		"push	r19				\n\t"	\
		"push	r20				\n\t"	\
		"push	r21				\n\t"	\
		"push	r22				\n\t"	\
		"push	r23				\n\t"	\
		"push	r24				\n\t"	\
		"push	r25				\n\t"	\
		"push	r26				\n\t"	\
		"push	r27				\n\t"	\
		"push	r28				\n\t"	\
		"push	r29				\n\t"	\
		"push	r30				\n\t"	\
		"push	r31				\n\t"	\
    );

#define __SCHED_RESTORE_CONTEXT()       \
    asm volatile (                      \
		"pop	r31				\n\t"	\
		"pop	r30				\n\t"	\
		"pop	r29				\n\t"	\
		"pop	r28				\n\t"	\
		"pop	r27				\n\t"	\
		"pop	r26				\n\t"	\
		"pop	r25				\n\t"	\
		"pop	r24				\n\t"	\
		"pop	r23				\n\t"	\
		"pop	r22				\n\t"	\
		"pop	r21				\n\t"	\
		"pop	r20				\n\t"	\
		"pop	r19				\n\t"	\
		"pop	r18				\n\t"	\
		"pop	r17				\n\t"	\
		"pop	r16				\n\t"	\
		"pop	r15				\n\t"	\
		"pop	r14				\n\t"	\
		"pop	r13				\n\t"	\
		"pop	r12				\n\t"	\
		"pop	r11				\n\t"	\
		"pop	r10				\n\t"	\
		"pop	r9				\n\t"	\
		"pop	r8				\n\t"	\
		"pop	r7				\n\t"	\
		"pop	r6				\n\t"	\
		"pop	r5				\n\t"	\
		"pop	r4				\n\t"	\
		"pop	r3				\n\t"	\
		"pop	r2				\n\t"	\
		"pop	r1				\n\t"	\
		"pop	r0				\n\t"	\
		"out 	__SREG__, r0	\n\t"	\
		"pop	r0				\n\t"	\
    );

/* Global (shush) variables for processes handling in interrupts*/
volatile uint8_t __sched_current = 0;
volatile struct running_process *__sched_procs = (void *)0;
uint8_t __sched_count = 0;
volatile uint16_t ms_counter = 0;

/* Handler */
ISR(TIMER2_COMPA_vect, ISR_NAKED){
    /* Stop current */
    __SCHED_SAVE_CONTEXT()
    __sched_procs[__sched_current].stack_pointer = SP;
	sei();
	
    /* If it is too early to stop process, resume. */
    if(++ms_counter < __sched_procs[__sched_current].ms)
        goto restore;
    ms_counter = 0;

	/* Witness */
	PORTB ^= (1 << PORT3);
    
    /* Find next process to schedule (simple Round Robin) */
    uint8_t next_proc = __sched_current;
    do{
        ++next_proc;
        if(next_proc == __sched_count) 
            next_proc = 0;
    }while(__sched_current != next_proc && __sched_procs[next_proc].status == STATUS_OFF);

    /* Next is the new current */
    __sched_current = next_proc;

    /* Restore/Create context */
    SP = __sched_procs[__sched_current].stack_pointer;
    switch (__sched_procs[__sched_current].status)
    {
    case STATUS_RUNNING:
		goto restore;
    case STATUS_INIT:
    default:
        __sched_procs[__sched_current].status = STATUS_RUNNING;
        __sched_procs[__sched_current].func();
    }
restore:
	__SCHED_RESTORE_CONTEXT()
	reti();
}

void start_scheduler(volatile struct running_process processes[], uint8_t count){
    cli();

    __sched_procs = processes;
    __sched_count = count;
    __sched_current = 0;

	/* Witness */
	DDRB |= (1 << PORTB3);

    /* Configure Timer 2 */
    /* Prescaler 128, f_CPU = 16MHz */
    /* TCNT LSB = 1/125 ms */
    /* OCR2A == 125 <=> Interruption toutes les ms */
    TCCR2A = 0b00000010;
    TCCR2B = 0b00000101;
    TCNT2  = 0;
    OCR2A  = 125;
    TIMSK2 = 0b00000010;

    /* Start process 0 and interrupts */
    __sched_procs[0].status = STATUS_RUNNING;
    SP = __sched_procs[0].stack_pointer;
    sei();
    __sched_procs[0].func();
}
