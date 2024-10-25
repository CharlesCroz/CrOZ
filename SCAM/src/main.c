#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "buzzer.h"

#define TIME_UNIT 1000

int main(void)
{
    tone_attach();
    while(1) //infinite loop
    {
        tone_set(400, 1000);
        tone_start();

        _delay_ms(3000);
    }

    return 0;
}