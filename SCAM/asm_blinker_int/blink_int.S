.text
.global reset
.global main
.global set_timer
.global TIM0_COMPA

;   LED
.equ    DDRB ,  0x04    ; 
.equ    PORTB , 0x05    ; 
.equ    PORTB5 , 5      ; 
;   TIMER0
.equ    TCCR0A , 0x24   ; 
.equ    TCCR0B , 0x25   ; 
.equ    TCNT0 , 0x26    ;
.equ    OCR0A , 0x27    ;
;   Enable Interrupts
.equ    TIMSK0 , 0x6E   ;
.equ    TIFR0 , 0x15    ;
.equ    TOV0 , 0        ;
.equ    OCF0A , 1       ;
;   SLEEP
.equ    SMCR , 0x33     ;

.org 0x0000                 ; changes interrupt vector table
    jmp reset               ; 
.org 0x0038                 ; 
    jmp TIM0_COMPA          ; goto TIM0_COMPA

reset:
    sbi     DDRB , PORTB5   ;   PIN13 OUT
    sbi     PORTB,  PORTB5  ;   START ON
    call    set_timer       ;   
    sei                     ;   Enable interrupts
main:
    rjmp    main            ;

set_timer:
    ldi     r16 , 0b00000010;   Deal with TCCR0A
    out     TCCR0A , r16    ;
    ldi     r16 , 0b00000101;   Deal with TCCR0B
    out     TCCR0B , r16    ;
    ldi     r16 , 0x00      ;   Deal with TCNT0
    out     TCNT0 , r16     ;
    ldi     r16 , 0xFF      ;   Deal with OCR0A
    out     OCR0A , r16     ;
    ldi     r16 , 0b00000010;   Deal with TIMSK0
    sts     TIMSK0, r16     ;
    ldi     r18 , 20        ;   prescaler2
    ret

TIM0_COMPA:
    dec r18                 ;   Decrease prescaler2
    breq switch_led         ;   If zero, reset and swtich LED
    reti                    ;   Else, return from interrupt
switch_led:
    ldi     r18, 10         ;   Reset prescaler2
    sbis    PORTB, PORTB5   ;   Check LED status
    rjmp    turn_on         ;   If not set, go to turn on
    cbi     PORTB, PORTB5   ;   If set, turn off
    reti                    ;   Return from interrupt 
turn_on:
    sbi     PORTB, PORTB5   ;   And turn on
    reti                    ;   Return from interrupt


