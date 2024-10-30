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
}

void test_led() {
    set_red_led(1);
    set_green_led(1);
    set_blue_led(1);

    imprecise_delay(250);

    set_red_led(0);
    set_green_led(0);
    set_blue_led(0);
}


void main(void) {
    setup();

    Color colors[16] = {};

    for (int16_t hue = 0; hue < 16; hue++) {
        colors[hue] = HSVtoRGB(hue * 16, 250, 250);
    }

    uint8_t counter = 0;
    uint8_t timer = 0;
    uint8_t hue = 0;

    uint8_t red_intensity = colors[0].r;
    uint8_t green_intensity = colors[0].g;
    uint8_t blue_intensity = colors[0].b;

    while(1) {
        set_red_led(red_intensity > counter);
        set_green_led(green_intensity > counter);
        set_blue_led(blue_intensity > counter);

        counter++;
        timer += counter > 240;

        if (timer == 0)
        {
            hue = hue == 16 ? 0 : hue + 1;

            red_intensity = colors[hue].r >> 6;
            green_intensity = colors[hue].g >> 6;
            blue_intensity = colors[hue].b >> 6;
        }
    }
}
