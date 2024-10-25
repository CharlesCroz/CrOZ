.text
.global main
.global waitXms

.equ    DDRB ,  0x04    ; 
.equ    PORTB , 0x05    ; 
.equ    PORTB5 , 5      ; 

main:
    sbi     DDRB, PORTB5    ;   PIN13 OUT
    sbi     PORTB, PORTB5   ;   PIN13 HIGH
main_loop:
    call    waitXms
    cbi     PORTB,  PORTB5  ;   PIN13 OFF
    call    waitXms
    sbi     PORTB,  PORTB5  ;   PIN13 ON
    jmp     main_loop       ;   Again
    ; sleep                   ;   Need help ?

waitXms:                    ; Wastes ~250ms of cycles
    ldi     r30,    0x41    ; ~= 4 000 000 cycles
    ldi     r31,    0x0F    ; ~= 1 024 * 0xF42
outerloop:
    ldi     r16,    0   ; Waits ~ 256 x 4 cycles
innerloop:
    dec     r16         ;
    brne    innerloop   ;
    sbiw    r30,    1   ;
    brne    outerloop   ;
    ret                 ;

