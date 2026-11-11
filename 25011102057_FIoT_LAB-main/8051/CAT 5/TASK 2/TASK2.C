#include <reg51.h>

int count=0;                // Counts PWM cycles
int brightness_counter=0;  // Controls the rate of brightness change
int level=0;                // Brightness level from 0 to 10
int dir=1;                  // Direction of brightness change
sbit led=P2^0;              // LED connected to P2.0

void main() {
	TMOD=0x01;               // Timer 0, Mode 1 (16-bit timer)
	TH0=0xFF;                // Load Timer 0 high byte
	TL0=0xA4;                // Load Timer 0 low byte
	TR0=1;                   // Start Timer 0
	led=0;                   // Initially turn LED OFF
	
	while(1) {
		if(TF0==1) {         // Check for Timer 0 overflow
			
			// Change brightness level after 1000 Timer overflows
			if(brightness_counter==999) {
				if(level==10) dir=-1;   // Start decreasing at maximum brightness
				if(level==0) dir=1;     // Start increasing at minimum brightness
				
				if(dir==1) level++;
				else if(dir==-1) level--;
				
				brightness_counter=0;
			}
			else brightness_counter++;
			
			// Keep LED OFF at minimum brightness
			if(level==0) {
				led=0;
				TF0=0;
				TH0=0xFF;
				TL0=0xA4;
				continue;
			}
			
			// Keep LED ON at maximum brightness
			if(level==10) {
				led=1;
				TF0=0;
				TH0=0xFF;
				TL0=0xA4;
				continue;
			}
			
			// Software PWM: compare PWM counter with brightness level
			if(count < level)
					led = 1;
			else
					led = 0;

			// Increment PWM counter and restart after 10 steps
			if(count == 9)
					count = 0;
			else
					count++;
			
			TF0=0;             // Clear Timer 0 overflow flag
			TH0=0xFF;          // Reload Timer 0 high byte
			TL0=0xA4;          // Reload Timer 0 low byte
		}	
	}
}