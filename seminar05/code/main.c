#include <xc.h>

#include "hsv_rgb.h"

// minimal config bits setup
#pragma config WDTEN = OFF      // Turn off the
#pragma config FOSC = INTIO7    // Pick internal clock
#pragma config MCLRE = EXTMCLR  // External reset pin
#pragma config FCMEN = ON       // Fail-Safe clock monitor

void imprecise_delay(uint32_t ms) {
    while (ms-- > 0) {
        for (uint16_t i = 0; i < 320; i++) {
            Nop();
        }
    }
}

void set_bit(volatile unsigned char* reg, uint8_t bit_number, uint8_t value) {
    // Check against invalid values.
    // if (bit_number >= 8 || value > 1) {
    //     return;
    // }

    *reg &= ~(1u << bit_number);
    *reg |= (value << bit_number);
}

void set_red_led(uint8_t value) {
    set_bit(&LATA, 2, value);
}

void set_green_led(uint8_t value) {
    set_bit(&LATA, 1, value);
}

void set_blue_led(uint8_t value) {
    set_bit(&LATA, 0, value);
}

// Switch numbered from 0 to 3.
uint8_t get_switch_state(uint8_t switch_number) {
    return (PORTC >> switch_number) & 1u;
}

void setup(void) {
    // internal oscillator at full speed (16 MHz).
    OSCCON = (OSCCON & 0b10001111) | 0b01110000;

    // Set led output
    TRISA &= ~0b111;

    // Set switch input
    TRISC = 0xF;
    ANSELC &= 0xF0; // Default values for <2:3> are 1.

    //disable global interrupts
    GIE = 0;

    T0CON = 0b11000111;     // Enable Timer0 and use 1:256 pre-scale
    TMR0IP = 1;             // High priority
    TMR0IE = 1;             // Enable interrupt
    IPEN = 1;               // Enable interrupt priority
    PEIE = 1;               // Enable peripheral interrupts

    // Enable global interrupt
    GIE = 1;
}

// Update led via index
void update_led(uint8_t idx, uint8_t state) {
    switch (idx) {
        case 0: set_red_led(state); break;
        case 1: set_green_led(state); break;
        case 2: set_blue_led(state); break;
    }
}

/* For debugging purposes to save our eyes :) */
volatile unsigned char imaginary_register = 42;

void set_imaginary_led(uint8_t value) {
    set_bit(&imaginary_register, 0, value);
}


void update_imaginary_led(uint8_t idx, uint8_t state) {
    switch (idx) {
        case 0: set_imaginary_led(state); break;
        case 1: set_imaginary_led(state); break;
        case 2: set_imaginary_led(state); break;
    }
}

// For simplicity for now, assume we just work with some static
// values that we might pre-compute later on during runtime.
const uint8_t first_idx = 1;
const uint8_t first_on = 0;

const uint8_t second_idx = 0;
const uint8_t second_on = 2;

const uint8_t third_idx = 2;
const uint8_t third_on = 0;

uint8_t all_off = 255 - first_on - second_on - third_on;

volatile uint8_t state = 0;

void __interrupt(high_priority) timer_interrupt(void) {
    if (TMR0IE && TMR0IF) {
        switch (state) {
            case 0:
                TMR0L = first_on;
                update_imaginary_led(first_idx, 1);
                update_imaginary_led(second_idx, 1);
                update_imaginary_led(third_idx, 1);
                state = 1;
                break;
            case 1:
                TMR0L = second_on;
                update_imaginary_led(first_idx, 0);
                state = 2;
                break;
            case 2:
                TMR0L = third_on;
                update_imaginary_led(second_idx, 0);
                state = 3;
                break;
            case 3:
                TMR0L = all_off;
                update_imaginary_led(third_idx, 0);
                state = 0;
                break;
        }

        TMR0IF = 0; // Clear interrupt flag
    }
}

void measure() {
    GIE = 0;

    set_red_led(0);
    set_green_led(0);
    set_blue_led(1);

    // There is some overhead caused by the 16 bit variable!
    for (uint16_t i = 0; i < 1000; i++) {
        // TODO: insert code from interrupt, use imaginary led :)
        switch (state) {
            case 0:
                TMR0L = first_on;
                update_led(first_idx, 1);
                update_led(second_idx, 1);
                update_led(third_idx, 1);
                state = 1;
                break;
            case 1:
                TMR0L = second_on;
                update_led(first_idx, 0);
                state = 2;
                break;
            case 2:
                TMR0L = third_on;
                update_led(second_idx, 0);
                state = 3;
                break;
            case 3:
                TMR0L = all_off;
                update_led(third_idx, 0);
                state = 0;
                break;
        }
    }

    set_blue_led(0);
}

void main(void) {
    setup();

    measure();

    while(1) {

    }
}
