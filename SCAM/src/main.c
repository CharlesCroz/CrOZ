#include <avr/io.h>
#include <util/delay.h>

#define DIGITAL13 0b00100000

void init(void)
{
    DDRB |= DIGITAL13;// Digital 13 "outputmode"
}

void led_on(){
    PORTB |= DIGITAL13;
}

void led_off(){
    PORTB &= ~DIGITAL13;
}

#define TIME_UNIT 120

int main(void)
{
    init();

    while(1) //infinite loop
    {
        led_on();
        _delay_ms(TIME_UNIT);
        led_off();
        _delay_ms(TIME_UNIT);
    }

    return 0;
}