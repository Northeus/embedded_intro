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

    T0CON = 0b11000000;     // Enable Timer0 and use 1:256 pre-scale
    TMR0IP = 1;             // High priority
    TMR0IE = 1;             // Enable interrupt
    IPEN = 1;               // Enable interrupt priority
    PEIE = 1;               // Enable peripheral interrupts

    // Enable global interrupt
    GIE = 1;
}

void __interrupt(high_priority) timer_interrupt(void) {
    if (TMR0IE && TMR0IF) {
        TMR0L = 32;
        LATA = pwm_values[state++];

        state &= 0b00111111;

        TMR0IF = 0; // Clear interrupt flag
    }
}

void set_pwm(uint8_t r, uint8_t g, uint8_t b) {
    for (uint16_t i = 0; i <= 64; i++) {
        pwm_values[i] = 0;

        if (i < r) pwm_values[i] |= 0b001;
        if (i < g) pwm_values[i] |= 0b010;
        if (i < b) pwm_values[i] |= 0b100;
    }
}

void main(void) {
    setup();

    set_pwm(2, 2, 0);

    while(1) {

    }
}
