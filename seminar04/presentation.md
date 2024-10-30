# Timers

---

# Agenda
 1. Revision of the previous seminar
 1. Basics of interrupts
 1. Basics of timers
 1. Implement simple timer for LED
 1. Upgrade solution from previous seminar to use timers

---

# Revision
 - Copy and paste [solution.c](https://github.com/Northeus/embedded_intro/tree/master/seminar03/code/solution.c)
 - Check the code together

---

# Interrupts
 - Code that reacts to some event
 - A main function is interrupted when the interrupt occurs
 - After the interrupt finish, the main function continues
 - They require some special function to be implemented - handler

---

# Timers
 - Idea: Registers that are being incremented (or decremented)
 - Can cause interrupts
 - Can be used to create a more precise delay function
 - Component to slow down the incrementing of timer - prescaler

---

# Assignment
 1. Check [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/40001412G.pdf) and find registers for timer setup:
    * Interrupts
    * Timers
 1. Implement simple timer interrupt that toggle our LED
 1. Implement an upgraded PWM that use timer interrupts

---

# Cheatsheet
 - T0CON
 - RCON: IPEN
 - INTCON: GIE, PEIE,
 - INTCON: TMR0IE, TMR0IF
 - INTCON2: TMR0IP
 - Header for bits: `#include <pic18f24k22.h>`

---

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
