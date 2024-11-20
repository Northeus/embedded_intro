# PWM - Servo

---

# Task 0: Init
 1. Download FRDM K66-F SDK
 1. Create new project with FTM driver

---

# Task 1: Pin setup
 1. Find SERVO pin in [schematics](https://github.com/Northeus/embedded_intro/tree/master/seminar08/schematic.pdf).
 1. Initialize SERVO pin to FTM in Pin config tool
 1. Setup SERVO pin as output

---

# Task 2: Specs
 1. Find servo specs on the internet.
 1. What is PWM signal period?
 1. What is PWM duty cycle duration?


---

# Task 3: Pheripheral setup
 1. Setup FTM to correct period.
 1. Setup FTM to dutycycle corresponding to neutral state.
 1. Check if your code work on car.

---

# Task 4: Update PWM
 1. Find how to update PWM (function).
 1. Extract logic and program high precision PWM update.
 1. Check if your code work on car.

---

# Bonus
 1. Use SCANF and PRINTF via UART to communicate board.
 1. Read number from user - angle (0 - 180).
 1. Update servo based on the given angle.

---

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
