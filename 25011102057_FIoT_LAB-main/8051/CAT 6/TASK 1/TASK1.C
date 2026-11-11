#include <reg51.h>

void main() {
    char message[] = "Hello from 8051";
    int i;
    int length;

    PCON = 0x00;       // Clear SMOD bit
    SCON = 0x40;       // UART Mode 1, 8-bit transmission
    TMOD = 0x20;       // Timer 1, Mode 2 (8-bit auto-reload)

    TH1 = 0xFD;        // 9600 baud rate for 11.0592 MHz crystal
    TL1 = 0xFD;
    TR1 = 1;           // Start Timer 1

    length = sizeof(message) - 1;  // Exclude null character

    while (1) {
        for (i = 0; i < length; i++) {
            SBUF = message[i];    // Load character into transmit buffer

            while (TI == 0);       // Wait for transmission to complete

            TI = 0;               // Clear transmit flag
        }
    }
}
