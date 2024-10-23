#include <xc.h>

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
    if (bit_number >= 8 || value > 1) {
        return;
    }

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

    test_led();

    while(1) {
        uint8_t override = get_switch_state(0);

        set_red_led(get_switch_state(1) && override);
        set_green_led(get_switch_state(2) && override);
        set_blue_led(get_switch_state(3) && override);

        imprecise_delay(20);
    }
}
