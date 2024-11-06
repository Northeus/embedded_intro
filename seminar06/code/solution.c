#include <xc.h>

#pragma config WDTEN = OFF      // Turn off the
#pragma config FOSC = INTIO7    // Pick internal clock
#pragma config MCLRE = INTMCLR  // Internal reset
#pragma config LVP = OFF        // Low level power off
#pragma config FCMEN = ON       // Fail-Safe clock monitor


/****************************************************************************/
/****************************************************************************/
/** Comment index and description     ** 'X' marks finished comments       **/
/****************************************************************************/
/** 0. Example                        **                 X                 **/
/** 1. Read ADC                       **                 X                 **/
/** 2. Swap PWM buffers               **                 X                 **/
/** 3. Detect button press            **                 X                 **/
/** 4. Button controled state machine **                 X                 **/
/** 5. Change RGB value using ADC     **                 X                 **/
/** 6. Update displayed LED value     **                 X                 **/
/****************************************************************************/
/****************************************************************************/


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
    // TODO (1) Read ADC value and return in.
    //          (hint: see ADCON0, ADRESH, and ADRESL registers)
    ADCON0 |= 0b10;                 // Start ADC conversion

    while (ADCON0 & 0b10) {         // Wait till the conversion finish
        Nop();
    }

    return (ADRESH << 2) | ADRESL;  // Read the measured value
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

    // TODO (2) When the pwm_counter reaches the last value,
    //          swap the front and back buffers.
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
    // TODO (3) Return 1 if there is an rising edge on the button signal.
    //          (hint: button routing is mentioned in setup function)
    //          (hint: you can store previous state of the button signal)
    button_prev = button_curr;
    button_curr = PORTE >> 3;

    return !button_prev && button_curr;
}

// Or use enum if you want to be fancy ;)
const uint8_t STATE_COUNT = 3u;

void main(void) {
    setup();
    set_pwm(0, 0, 0);

    // Feel free to add any variables you might need :)
    uint8_t state = 0u;
    uint8_t rgb[3] = {0u, 0u, 0u};

    while(1) {
        // TODO (4) Implement a state machine with three state where
        //          each state corresponds to a single color from RGB.
        //          The state should be changed whenever a button press
        //          occurre.
        //          (hint: use function is_pressed)
        if (is_pressed()) {
            state = (state + 1) % STATE_COUNT;
        }

        // TODO (5) Update color using ADC value given by read_adc function
        //          based on the current state of the state machine, which
        //          specify the color.
        //
        //          It is better to use only top three bits from read value
        //          to lower the intensity of the LEDs, so discard the lower
        //          seven bits of the ten bits ADC value.
        rgb[state] = read_adc() >> 7;

        // TODO (6) Set the PWM using function set_pwm to display the
        //          RGB values that are currently set.
        set_pwm(rgb[0], rgb[1], rgb[2]);
    }
}
