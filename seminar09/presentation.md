# Line Camera

---

# Task 0: Init
 1. Create new project with ADC and PIT drivers

---

# Task 1: ADC setup
 1. Initialize ADC peripheral to 12-bit
 1. Route PTB5 pin to ADC1

---

# Task 2: PIT setup
 1. Initialize PIT peripheral to 60MHz clock

---

# Task 3: Implement helper functions
 1. Implement function reading ADC value
 1. Implement function for delay in microseconds
 1. If needed, use [helpers.cpp](https://github.com/Northeus/embedded_intro/tree/master/seminar09/code/helpers.cpp)

---

# Task 4: Load one frame from camera
 1. Check [datasheet](https://www.farnell.com/datasheets/315815.pdf) and [manual](https://www.mouser.com/datasheet/2/321/28317-TSL1401-DB-Manual-369950.pdf?srsltid=AfmBOop-ajw2Oq4FS2JzxYxr9Zd8QeP86ALP0uedSpyU1tLMjvPH55mA)
 1. Create pulse on SI pin (PTB19) and produce clock signal on CLK pin (PTB18)
 1. Read ADC value according to the datasheet
 1. Return 128 values read from ADC

---

# Task 5: Show data from camera
 1. Read one frame and discard it
 1. Wait exposition time (preferred 5000us)
 1. Read another frame and print it

---

# Notes
 - Required functions for solution are in [solution.cpp](https://github.com/Northeus/embedded_intro/tree/master/seminar09/code/solution.cpp)
 - Whole project is stored in [solution.zip](https://github.com/Northeus/embedded_intro/tree/master/seminar09/code/solution.zip)
 - Visualization script is [visualize.py](https://github.com/Northeus/embedded_intro/tree/master/seminar09/code/solution.zip)


---

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
