# Introduction to programming in C

---

# Who are we?

![logo](https://emlab.fi.muni.cz/_media/wiki/logo.png)

---

# Who are you?
 - What are you interested in?
 - Is there anything you would like to see in this course?

---

# Course overview
 1. Intro to programming in C
 1. Basic microcontroller programming, GPIO
 1. Timers, PWM, and LED intensity controlling
 1. Analog signal
 1. Display
 1. Serial communication (UART)
 1. Sensors, and advanced peripherals
 1. Programming self-driving car, and project selection
 1. Working on the project
 1. Project finalization, what now

---

# Hardware
 - 8-bit PIC controllers
 - Really low level programming (working with registers)
 - Some seminars might include 32-bit ARM controllers for more advanced stuff
 - Sensors used within this course might be changed based on your needs

---

# Basic C program ([basic_program.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/basic_program.c))
 - Include standard library to use print.
 - Main function.

---

# Basic data types in C ([data_types.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/data_types.c))
 - Representation of numbers and characters in computer via bytes
 - Signed (two-complements) vs. unsigned numeric types
 - Strings of characters are stored in ASCII format
 - Integers: `int`, `unsigned int`, `long`, `unsigned long`, ...
 - Fixed size integers: `int8_t`, `uint8_t`, ... (see [stdint.h](https://en.cppreference.com/w/c/types/integer))
 - Floating point numbers: `float`, and `double`
 - Characters: `char`, and `char*`

---

# Aggregate data types ([aggregate_data_types.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/aggregate_data_types.c))
 - Structs can compose multiple different data types
 - Arrays allow us to store multiple data of the same type

![array](https://media.geeksforgeeks.org/wp-content/uploads/20230302091959/Arrays-in-C.png)

---

# Operators ([operators.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/operators.c))
 - Arithmetic: `+`, `-`, `*`, `/`, and `%`
 - Logic: `==`, `!=`, `!`, `&&`, and `||`
 - Bit: `&`, `|`, `^`, and `~`
 - Increment and decrement: `++x`, `x++`, `--x`, and `x--`
 - shorthand `a = a + b` is same as `a += b`

---

# Building blocks ([building_blocks.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/building_blocks.c))
 - Loops: `for`, `while`, and `do ... while`
 - Skip loop: `continue`, and `break`
 - Conditionals: `if`, `else`, and ternary
 - `switch` with `case`, `break`
 - Functions
 - Macros
 - Jumps

---

# Memory ([memory.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/memory.c))
 - Stack (static) vs. heap (dynamic)
 - Referencing variables to obtain their addresses within memory.
 - Dereference addresses to get values from the given memory location.

---

# Code separation
 - Code can be separated into multiple functions
 - Each function can be stored in a different file
 - Use header files to link functions from different file via `#include`
 - Include from predefined directories vs. from project files

---

# Let's finally code something ([tasks.c](https://github.com/Northeus/embedded_intro/tree/master/seminar01/code/tasks.c))
 1. Copy the file with tasks to your computer
 1. Read the comments carefully
 1. Implement the desired functionality marked with `TODO` comments
 1. Check the outcome of asserts
 1. If any problems occur, go back to the third step

---

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
