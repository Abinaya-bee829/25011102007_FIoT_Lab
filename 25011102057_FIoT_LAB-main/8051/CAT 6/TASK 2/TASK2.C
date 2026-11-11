#include <reg51.h>

void uart_init() {
    PCON = 0x00;       // SMOD = 0: Normal baud rate
    SCON = 0x50;       // UART Mode 1, 8-bit, receiver enabled
    TMOD = 0x20;       // Timer 1, Mode 2 (8-bit auto-reload)

    TH1 = 0xFD;        // 9600 baud for 11.0592 MHz crystal
    TL1 = 0xFD;

    TR1 = 1;           // Start Timer 1

    TI = 0;
    RI = 0;
}

void uart_transmit(char ch) {
    SBUF = ch;         // Load character for transmission

    while (TI == 0);   // Wait until transmission completes

    TI = 0;            // Clear transmit flag
}

char uart_receive() {
    char ch;

    while (RI == 0);   // Wait until a character is received

    ch = SBUF;         // Read received character

    RI = 0;            // Clear receive flag

    return ch;
}

void main() {
    char received;

    uart_init();

    while (1) {
        received = uart_receive();  // Receive from PuTTY
        uart_transmit(received);    // Send the same character back
    }
}

