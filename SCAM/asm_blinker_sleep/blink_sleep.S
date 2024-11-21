.text
.global reset
.global set_timer
.global TIM2_COMPA

;   LED
.equ    DDRB ,  0x04    ; 
.equ    PORTB , 0x05    ; 
.equ    PORTB5 , 5      ; 
;   TIMER0
.equ    TCCR2A , 0xB0   ; 
.equ    TCCR2B , 0xB1   ; 
.equ    TCNT2 , 0xB2    ;
.equ    OCR2A , 0xB3    ;
;   Enable Interrupts
.equ    TIMSK2 , 0x70   ;
;   SLEEP
.equ    SMCR , 0x33     ;

.org 0x0000                 ; changes interrupt vector table
    jmp reset               ; 
.org 0x003C                 ; 
    jmp TIM2_COMPA          ; goto TIM2_COMPA

reset:
    sbi     DDRB , PORTB5   ;   PIN13 OUT
    sbi     PORTB,  PORTB5  ;   START ON
    call    set_timer       ;   
    sei                     ;   Enable interrupts
main:
    ldi     r16 , 0b0100    ;   Idle mode
    out     SMCR , r16      ;
    sleep                   ;   Sleep
    rjmp    main            ;

set_timer:
    ldi     r16 , 0b00000010;   Deal with TCCR2A
    sts     TCCR2A , r16    ;
    ldi     r16 , 0b00000111;   Deal with TCCR2B
    sts     TCCR2B , r16    ;
    ldi     r16 , 0x00      ;   Deal with TCNT2
    sts     TCNT2 , r16     ;
    ldi     r16 , 0xFF      ;   Deal with OCR2A
    sts     OCR2A , r16     ;
    ldi     r16 , 0b00000010;   Deal with TIMSK2
    sts     TIMSK2, r16     ;
    ldi     r18 , 10        ;   prescaler2
    ret

TIM2_COMPA:
    dec     r18             ;   Decrease prescaler2
    breq    switch_led      ;   If zero, reset and swtich LED
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


