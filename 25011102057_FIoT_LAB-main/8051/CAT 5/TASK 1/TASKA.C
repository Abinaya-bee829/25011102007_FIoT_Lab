#include <reg51.h>

int count=0;          // Counts Timer 0 overflows
sbit led=P2^0;        // LED connected to P2.0

// Toggle the LED state
void toggle_led(){
	led=!led;
}

void main() {
	TMOD=0x01;          // Timer 0, Mode 1 (16-bit timer)
	TH0=0xFC;           // Load Timer 0 high byte
	TL0=0x66;           // Load Timer 0 low byte
	TR0=1;              // Start Timer 0
	
	while(1) {
		if(TF0==1) {    // Check for Timer 0 overflow
			if(count==500) {
				toggle_led();   // Toggle LED after 500 overflows
				count=0;        // Reset overflow counter
			}
			else count++;
			
			TF0=0;          // Clear Timer 0 overflow flag
			TH0=0xFC;       // Reload Timer 0 high byte
			TL0=0x66;       // Reload Timer 0 low byte
		}
	}
}