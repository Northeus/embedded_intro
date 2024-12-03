#include <xc.h>

#pragma config WDTEN = OFF      // Turn off the
#pragma config FOSC = INTIO7    // Pick internal clock
#pragma config MCLRE = INTMCLR  // Internal reset
#pragma config LVP = OFF        // Low level power off
#pragma config FCMEN = ON       // Fail-Safe clock monitor

void setup(void) {
    // internal oscillator at full speed (16 MHz).
    OSCCON = (OSCCON & 0b10001111) | 0b01110000;

    // Set LED pins RA0, RA1, and RA2 as a digital output.
    // Set potentiometer pin RA3 as an analog input.
    TRISA = (uint8_t) ~0b111;
    ANSELA = 0xFF;

    // Set switch pins RC0, RC1, RC2, and RC3 as a digintal input.
    TRISC = 0x0F;
    ANSELC = 0xF0;

    // Button pin RE3 defaults to digital input

    //disable global interrupts
    GIE = 0;

    // Setup timer interrupt without pre-scaler
    T0CON = 0b11000000;     // Enable Timer0 and use 1:1 pre-scale
    TMR0IP = 1;             // High priority
    TMR0IE = 1;             // Enable interrupt
    IPEN = 1;               // Enable interrupt priority
    PEIE = 1;               // Enable peripheral interrupts

    // Enable global interrupt
    GIE = 1;

    // Setup ADC for RA3 (AN3) pin
    ADCON0 = 0b1101;        // Enable ADC and setup it for AN3 pin
    ADCON1 = 0;             // Leave default values
    ADCON2 = 0b00010101;    // Setup acquisition time (see TABLE 17-1)
}

uint16_t read_adc() {
    ADCON0 |= 0b10;                 // Start ADC conversion

    while (ADCON0 & 0b10) {         // Wait till the conversion finish
        Nop();
    }

    return (ADRESH << 2) | (ADRESL >> 6);  // Read the measured value
}

// Double buffering
volatile uint8_t buffer1[64];
volatile uint8_t buffer2[64];
volatile uint8_t* pwm_front_buffer = buffer1;
volatile uint8_t* pwm_back_buffer = buffer2;

volatile uint8_t pwm_counter = 0;

// Pre-compute and set PWM values for given RGB values from range 0-64
void set_pwm(uint8_t r, uint8_t g, uint8_t b) {
    for (uint16_t i = 0; i <= 64; i++) {
        pwm_back_buffer[i] = 0;

        if (i < r) pwm_back_buffer[i] |= 0b001;
        if (i < g) pwm_back_buffer[i] |= 0b010;
        if (i < b) pwm_back_buffer[i] |= 0b100;
    }

    while (pwm_counter != 63) {
        Nop();
    }

    volatile uint8_t* tmp = pwm_front_buffer;
    pwm_front_buffer = pwm_back_buffer;
    pwm_back_buffer = pwm_front_buffer;
}

void __interrupt(high_priority) timer_interrupt(void) {
    if (TMR0IE && TMR0IF) {             // Check if interrupt is caused by Timer0
        TMR0L = 32;                     // Some constant delay
        LATA = pwm_front_buffer[pwm_counter++];     // Set pre-computed state for LEDs

        pwm_counter &= 0b00111111;            // If state overflow, reset it

        TMR0IF = 0;                     // Clear interrupt flag
    }
}

volatile uint8_t button_prev = 0u;
volatile uint8_t button_curr = 0u;

uint8_t is_pressed() {
    button_prev = button_curr;
    button_curr = PORTE >> 3;

    return !button_prev && button_curr;
}

const uint8_t STATE_COUNT = 3u;

typedef struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

Color HSVtoRGB(int16_t hue, int16_t saturation, int16_t value) {
    if (saturation == 0) {
        return (Color) {.r = value, .g = value, .b = value};
    }

    int16_t region = hue / 43;

    int16_t remainder = (hue - (region * 43)) * 6;

    int16_t P = (value * (255 - saturation)) >> 8;
    int16_t Q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
    int16_t T = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    switch (region) {
        case 0:
            red = (uint8_t) value;
            green = (uint8_t) T;
            blue = (uint8_t) P;

            break;
        case 1:
            red = (uint8_t) Q;
            green = (uint8_t) value;
            blue = (uint8_t) P;

            break;
        case 2:
            red = (uint8_t) P;
            green = (uint8_t) value;
            blue = (uint8_t) T;

            break;
        case 3:
            red = (uint8_t) P;
            green = (uint8_t) Q;
            blue = (uint8_t) value;

            break;
        case 4:
            red = (uint8_t) T;
            green = (uint8_t) P;
            blue = (uint8_t) value;

            break;
        default:
            red = (uint8_t) value;
            green = (uint8_t) P;
            blue = (uint8_t) Q;
    }

  return (Color) {.r = red, .g = green, .b = blue};
}

void imprecise_delay(uint32_t ms) {
    while (ms-- > 0) {
        for (uint16_t i = 0; i < 320; i++) {
            Nop();
        }
    }
}

void main(void) {
    setup();
    set_pwm(0, 0, 0);

    uint8_t state = 0u;
    uint8_t rgb[3] = {0u, 0u, 0u};
    
    Color colors[64] = {0};
    uint8_t i = 0;

    for (int16_t hue = 0; hue < 64; hue++) {
        colors[hue] = HSVtoRGB(hue * 4, 250, 250);
    }

    while(1) {
        if (((PORTC & 0b1100) != 0) && ((PORTC & 0b0011) != 0)) {
            if (is_pressed()) {
                state = (state + 1) % STATE_COUNT;
            }

            rgb[state] = read_adc() >> 7;

            set_pwm(rgb[0], rgb[1], rgb[2]);
            
            continue;
        } 
        
        if ((PORTC & 0b0011) != 0) {
            imprecise_delay(200);
            
            Color color = colors[i];
            i = i < 63 ? (i + 1) : 0;
            
            set_pwm(color.r >> 5, color.g >> 5, color.b >> 5);
        
            continue;
        }
        
        if ((PORTC & 0b1100) != 0) {
            imprecise_delay(200);
            
            uint8_t adc = read_adc() >> 1;
            Color color = HSVtoRGB(adc, 250, 250);
            
            set_pwm(color.r >> 5, color.g >> 5, color.b >> 5);
        
            continue;
        }
        
        set_pwm(0, 0, 0);
    }
}
