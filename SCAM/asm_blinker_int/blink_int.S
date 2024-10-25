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
;   SLEEP
.equ    SMCR , 0x33     ;

.org 0x0000                 ; changes interrupt vector table
    jmp reset               ; 
.org 0x0038                 ; 
    jmp TIM0_COMPA          ; goto TIM0_COMPA

.org 0x0068
reset:
    eor     r1, r1
    out     0x3f, r1        ; 63
    ldi     r28, 0xFF       ; 255
    ldi     r29, 0x08       ; 8
    out     0x3e, r29       ; 62
    out     0x3d, r28       ; 61
    sbi     DDRB , PORTB5   ;   PIN13 OUT
    sbi     PORTB,  PORTB5  ;   START ON
    call    set_timer       ;   
    sei                     ;   Enable interrupts
main:
    rjmp    main            ;
    ; ldi     r16 , 0b1101    ;
    ; out     SMCR , r16      ;
    ; sleep                   ;   Sleep

set_timer:
    ldi     r16 , 0b00000010;   Deal with TCCR0A
    out     TCCR0A , r16    ;
    ldi     r16 , 0b00000101;   Deal with TCCR0B
    out     TCCR0B , r16    ;
    ldi     r16 , 0x00      ;   Deal with TCNT0
    out     TCNT0 , r16     ;
    ldi     r16 , 0xFF      ;   Deal with OCR0A
    out     OCR0A , r16     ;
    ldi     r16 , 0b00000011;   Deal with TIMSK0
    sts     TIMSK0, r16     ;
    ret

TIM0_COMPA:
    sbi     TIFR0, TOV0     ;
    sbis    PORTB, PORTB5   ;
    breq    turn_on         ;
    cbi     PORTB, PORTB5   ;
    reti                    ;
turn_on:
    sbi     PORTB, PORTB5   ;
    reti                    ;


