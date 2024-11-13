# Higher Level Programming

---

# Agenda
 1. MCU Expresso IDE
 1. GPIO - button and LED
 1. GPIO - interrupts
 1. PIT - timing
 1. PWM - LED brightness controlling

---

# MCU Expresso IDE
 - Allows us to:
   * Configure generated  set-up code
   * Compile our project
   * Flash project to board
   * Debug
 - Reset IDE layout: Toolbar -> Window -> Perspective -> Reset Perspective

---

# MCU Expresso IDE - SDK
 - Kit containing drivers, examples related to a board
 - Install SDK:
   1. Chose workspace, close welcome page
   1. Go to "Installed SDKs" panel (bottom middle tab)
   1. Right-click on the empty space
   1. Chose "Download and Install SDKs"
   1. Find "frdmmcxn947" SDK and install it

---

# MCU Expresso IDE - New Project
 - To create a new project:
   1. Go to "Quickstart Panel" (bottom left tab)
   1. Click on "Create a new C/C++ project..."
   1. Find "frdmmcxn947" SDK and click "next"
   1. Change "Project type" to "C++ Project"
   1. Change "SDK Debug Console" to "Semihost"

---

# Hello world
 - We can print into console \o/
 - use `PRINTF` function MACRO the same way as usual prinf

---

# Pin Setup Tool
 - Allows us to configure pins
 - Go to Toolbar -> ConfigTools -> Pins
 - Search pins in Pins panel (on the left)
 - Click on the square in the first column and route it to correct peripheral
 - See "Routing details" for pin configuration on the bottom

---

# Configure Pins
 1. In "Functional groups" pick "BOARD_InitLEDsPins"
 1. Click on the flag on the right to turn on this group
 1. See how the pins are configured in "Routing Details"
 1. Do the same for "BOARD_InitBUTTONsPins" functional group

---

# Peripherals Setup Tool
 - Allows us to configure peripherals (PWM, timers)
 - Go to Toolbar -> ConfigTools -> Pins

---

# Assignment (together)
 1. Look at the generated project stucture
 1. Check GPIO drivers in code
 1. Check pin setup in code
 1. Find functions for handling GPIO

---

# Assignment (Alone)
 1. Read button state
 1. Print something upon button press
 1. Change led whe the button is pressed

# Bonus: Interrupts
 1. Update pin config to allows interrupts on button pins
 1. Add GPIO interrupt peripheral using Peripheral setup tool
 1. Copy and paste interrupt handler into code
 1. Handle button press events using interrupts instead of polling

---

# Bonus: PIT
 1. Setup PIT peripheral to generate periodic interrupts
 1. Print something to console every 3 seconds
 1. Add code for PIT handling

---

# Bonus: PWM
 1. Setup PWM peripheral
 1. Update pin config to route LED from GPIO to PWM
 1. Add code for PWM handling

<style>
    img[alt~="center"]
    {
        display: block;
        margin: 0 auto;
    }
</style>

![w:640 center](https://static.wikia.nocookie.net/multiversus/images/d/db/ROThumb_ThatsAllFolks.png)
