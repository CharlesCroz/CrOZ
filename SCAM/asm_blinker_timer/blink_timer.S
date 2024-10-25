.text
.global reset
.global main

;   LED
.equ    DDRB ,  0x04    ; 
.equ    PORTB , 0x05    ; 
.equ    PORTB5 , 5      ; 
;   TIMER0
.equ    TCCR_A , 0x24   ; 
.equ    TCCR_B , 0x25   ; 
.equ    TCNT_ , 0x26    ;
.equ    OCR_A , 0x27    ;
;   Enable Interrupts
.equ    TIFR_ , 0x15    ;
.equ    TOV0 , 0        ;
.equ    OCF_A , 1       ;
;   SLEEP
.equ    SMCR , 0x33     ;

.org 0x0000                 ; changes interrupt vector table
    jmp reset               ; 

reset:
;   Program requirements
    sbi     DDRB , PORTB5   ;   PIN13 OUT
    ldi     r16 , 0b00000010;   Deal with TCCR_A
    out     TCCR_A , r16    ;
    ldi     r16 , 0b00000101;   Deal with TCCR_B
    out     TCCR_B , r16    ;
    ldi     r16 , 0xFF      ;   Deal with OCR_A
    out     OCR_A , r16     ;
    ldi     r18, 10         ;   N times counter
main:
    sbis    TIFR_, OCF_A    ;   Check COMPA flag
    rjmp    main            ;   If clear, jump back and check again
    sbi     TIFR_, OCF_A    ;   If set, clear bit
    dec     r18             ;   r18--
    brne    main            ;   If not 0, wait for one more COMPA
    ldi     r18, 10         ;   If 0, reset r18, and szitch LED
    sbis    PORTB, PORTB5   ;   Check LED status
    rjmp    turn_on         ;   If not set, go to turn on
    cbi     PORTB, PORTB5   ;   If set, turn off
    rjmp    main            ;   Again
turn_on:
    sbi     PORTB, PORTB5   ;   And turn on
    rjmp    main            ;   Again
