#include <xc.h>

// minimal config bits setup
#pragma config WDTEN = OFF      // Turn off the
#pragma config FOSC = INTIO7    // Pick internal clock
#pragma config MCLRE = EXTMCLR  // External reset pin
#pragma config FCMEN = ON       // Fail-Safe clock monitor

void main(void) {
    // internal oscillator at full speed (16 MHz)
    OSCCON = (OSCCON & 0b10001111) | 0b01110000;

    while(1) {
    }
}
