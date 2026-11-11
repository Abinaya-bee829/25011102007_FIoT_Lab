#include <reg51.h>

sbit E=P3^3;    // LCD Enable pin

// Software delay for LCD timing
void delay(int n) {
	int i;
	int j;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
		}
	}
	E=0;          // Disable LCD
}

void main() {
	// Function Set
	P3=0x28;       // Send upper nibble
	delay(250);
	P3=0x08;       // Send lower nibble
	delay(250);
	
	// Display, Cursor
	P3=0x08;       // Send upper nibble
	delay(250);
	P3=0xF8;       // Display ON, cursor ON, blinking
	delay(250);

	
	// Incrementing
	P3=0x08;       // Send upper nibble
	delay(250);
	P3=0x68;       // Set entry mode to increment cursor
	delay(250);
	
	// Clear Display
	P3=0x08;       // Send upper nibble
	delay(500);
	P3=0x18;       // Clear display command
	delay(500);
	
	while(1) {
		P3=0x4C;     // Send upper nibble of display data
		delay(100);
		P3=0x3C;     // Send lower nibble of display data
		delay(100);
	}
}