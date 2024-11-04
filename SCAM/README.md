# SCAM (Scheduler and Calls on Arduino for Morse)

## Tools

### AVR Dude

```
sudo apt-get update
sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr avrdude
```

### Ports

May require to change the output `TERM` in the Makefile to point your Arduino device in `/dev`.

## HW Setup

- Witness LED (and resistor) on PORTB3 (Arduino Pin 11)
- Green LED (and resistor) on PORTB4 (Arduino Pin 12)
- Red LED (and resistor) on PORTB5 (Arduino Pin 13)
- Piezo buzzer (and resistor) on PORTB2 (Arduino Pin 10)
- LCD Keypad Shield


## Versions

### ASM Blinkers

Some preliminary work about Arduino ASM, registers, timers, and compiler options :
- **loop** : Estimated blinking period using the count and duration of instructions.
- **timer** : Internal timer used to raise a flag. Main loop reads the flag.
- **int** : Interrupt is attached to the timer. Main section doesnt do much but set the timer and interrupts then an idle loop.
- **sleep** : Main section enters sleep mode to save power between LED szitches.


### Sched

Incremental implementations of a scheduler :
- **v0** : switch between processes. Saves and restores context.
- **v1** : Add global timer.
- **v1** : Add global timer.
