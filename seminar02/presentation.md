# Intro to embedded programming

---

# Agenda
 1. Intro to MPLAB X IDE
 1. Flashing your own first program
 1. Reading a datasheet
 1. Playing with GPIO

---

# Create project
 - We use PIC18F24k22 boards
 - Create new main file in source directory
 - Copy and paste [main.c](https://github.com/Northeus/embedded_intro/tree/master/seminar02/code/main.c)
 - Try flash the board and see if there are any errors

---

# GPIO
 - Logical vs Physical value
 - Read logical values from pins
 - Write logical values to pins

---

# Reading the datasheet
 - We will work with registers
 - Each bit of those registers has some meaning
 - Try to find out how to read and write value to a PIN
 - [Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/40001412G.pdf)

---

# Checkpoint
 - TRISx - set pin to read (!write) state
 - PORTx - read value from pin
 - LATx - write pin value

---

# Lets check the schematics
 - Now we know how to work with pins
 - See [schematic](https://github.com/Northeus/embedded_intro/tree/master/seminar02/schematic.pdf)
 - Find out what pins are connected to the LED and switches

---

# Checkpoint
 - RA0, RA1, RA2 - LED
 - RC0, RC1, RC2, RC3 - Switches

---

# Assignment
 - Be aware that LED is a quite powerful
 - Assign LED to turn ON / OFF based on the switch

---

# Delay
 - First see the assemply of our code
 - Window -> Debugging -> Output -> Dissasembly listing file
 - Try to create a precise bussy delay for miliseconds.

---

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
