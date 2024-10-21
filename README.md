# CrOZ

A Cute & ridiculous Operating Zystem

## The Why

This is a personnal project I started as a way for me to understand better what the OS does, and try to implement a basic (so basic it deserves the adjectives "cute"  and " ridiculous") Operating Zystem on the HW I have at hand. The project is divided in subprojects to deal with increasing complexity and the different chips I play with.

There is no difference between an Operating System (OS) and an Operating Zystem (OZ), it is just a pun with my name. Sorry.

Past, present, and future forms of the verbs will be updated as the projects move forward.

## The What

### SCAM (Scheduler and Calls on Arduino for Morse)

This first project is a first attempt at this daunting task of making an OS. Its aim is for me to get familiar with writing ASM and C on a simple enough architecture, as well as getting familiar with some tools (debug, emulation, compilation toolchains). The support is a device that can synthetize sound.  

The HW is an Arduino Uno R3 with a (find screen ref), a (find button ref), and a buzzer.

The supported functionalities are:
- Up to N (tbd) running process at the same time. Process can be:
    - A "start/stop process" menu
    - A timer (set delay in seconds/start/stop)
    - A note (use arrows to save a message on the display)
    - A process that will play the morse sound of a string
- One task is running in the foreground, the other in the background.
- Process scheduling
    - Round robin
    - Process can be "sleeping" (wake up time tested before scheduling)
    - Process can be "waiting for a resource" (e.g. a timer waits for the end of a morse sequence before it rings)
- System calls using interrupts
    - Print on screen
    - Play sound
    - Get keypress
    - Sleep n millis

### Upcoming

The second project will be an simple hypervisor on a single core Cortex-A9 chip. We will see what it does when we get there, but here are things I have in mind :
- protected vs user mode
- file system
- IPCs
- ...