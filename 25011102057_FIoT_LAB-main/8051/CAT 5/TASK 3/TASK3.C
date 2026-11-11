#include <reg51.h>

int count=0;          // Counts Timer 0 interrupts
int step=0;           // Current step of the motor sequence
int key=0;             // Selected speed mode

// Stepper motor control pins
sbit bit0=P3^0;
sbit bit1=P3^1;
sbit bit2=P3^2;
sbit bit3=P3^3;

// Speed selection keypad pins
sbit ROW=P2^7;
sbit slow=P2^3;
sbit medium=P2^2;
sbit fast=P2^1;

// Timer 0 interrupt routine
void timer_0() interrupt 1 {
	count++;
	TF0=0;
	TH0=0xFC;
	TL0=0x66;
}

// Software delay for keypad debounce
void delay() {
	int i;
	int j;
	for(i=0; i<50; i++) {
		for(j=0; j<50; j++) {
		}
	}
}

// Generate the four-step sequence for the stepper motor
void movement(){
	if(step==0) {
		bit0=1;
		bit1=bit2=bit3=0;
	}
	if(step==1) {
		bit1=1;
		bit0=bit2=bit3=0;
	}
	if(step==2) {
		bit2=1;
		bit1=bit0=bit3=0;
	}
	if(step==3) {
		bit3=1;
		bit1=bit2=bit0=0;
	}
}

// Slow mode: change motor step after 100 Timer 0 interrupts
void mode_1() {
			if(count==99) {
				movement();
				count=0;
				step++;
				if(step==4) step=0;
			}
			
}

// Medium mode: change motor step after 50 Timer 0 interrupts
void mode_2() {
			if(count==49) {
				movement();
				count=0;
				step++;
				if(step==4) step=0;
			}
}

// Fast mode: change motor step after 10 Timer 0 interrupts
void mode_3() {
			if(count==9) {
				movement();
				step++;
				count=0;
				if(step==4) step=0;
			}
}

// Scan the keypad and return the selected speed
int keypad_scan() {
	ROW=0;
	slow=medium=fast=1;
	
	// Check slow-speed button
	if(slow==0) {
		delay();
		if(slow==0) {
			while(!slow);
			return 1;
		}
	}
	
	// Check medium-speed button
	if(medium==0) {
		delay();
		if(medium==0) {
			while(!medium);
			return 2;
		}
	}
	
	// Check fast-speed button
	if(fast==0) {
		delay();
		if(fast==0) {
			while(!fast);
			return 3;
		}
	}
	return 0;
}	

void main() {
	int newkey;
	int previous_key=0;
	
	TMOD=0x01;          // Timer 0, Mode 1 (16-bit timer)
	TH0=0xFC;           // Load Timer 0 high byte
	TL0=0x66;           // Load Timer 0 low byte
	EA=1;               // Enable global interrupts
	ET0=1;              // Enable Timer 0 interrupt
	TR0=1;              // Start Timer 0
	
	while(1) {
		newkey=keypad_scan();
		
		// Detect a new key press
		if(newkey != 0 && previous_key == 0) {
			key = newkey;
			count = 0;
		}
		
		previous_key = newkey;
		
		// Run the selected motor speed mode
		switch(key) {
			case 1:
				mode_1();
				break;
			
			case 2:
				mode_2();
				break;
			
			case 3:
				mode_3();
				break;
		}
	}
}