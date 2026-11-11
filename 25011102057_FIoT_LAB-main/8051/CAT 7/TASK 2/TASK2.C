#include <reg51.h>

sbit E=P3^3;       // LCD Enable pin
int count=0;       // Tracks current LCD position

// Software delay for LCD timing
void delay(int n) {
	int i;
	int j;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
		}
	}
	E=0;
}

// Send an LCD command in 4-bit mode
void lcd_cmd(unsigned char cmd, int n) {
	P3=(cmd & 0xF0) | 0x08;   // Send upper nibble with RS=0
	delay(n);
	P3=(cmd<<4) |0x08;        // Send lower nibble with RS=0
	delay(n);
}

// Send a character/data byte to the LCD
void lcd_data(unsigned char ch, int n) {
	P3=(ch & 0xF0) | 0x0C;    // Send upper nibble with RS=1
	delay(n);
	P3=(ch<<4) |0x0C;         // Send lower nibble with RS=1
	delay(n);
	count++;
}

// Move LCD cursor to the specified row and column
void lcd_goto(char row, char col) {
	char address;
	if(row==1) {
		address=0x00+col-1;
		count=col-1;
	}
	else if(row==2) {
		address=0x40+col-1;
		count=16+col-1;
	}
	else return;
	
	lcd_cmd(0x80 | address, 300);   // Set DDRAM address
}

// Display a string on the LCD
void lcd_puts(char s[]) {
	int i;

    for(i = 0; s[i] != '\0'; i++)
    {
			if(count==16) lcd_goto(2, 1);   // Move to second row
			if(count==32) {
				lcd_cmd(0x01, 500);          // Clear display
				count=0;
			}					
      lcd_data(s[i], 100);
    }
}

// Display an integer number on the LCD
void lcd_print_number(int num) {
	char arr[32];
	int i=0;
	int j;
	bit isNegative=0;

	if(num==0) {
		lcd_data('0', 250);
		return;
	}

	// Check if the number is negative
	if(num<0) {
		isNegative=1;
		num=-num;
	}

	// Extract digits in reverse order
	while (num!=0) {
		arr[i]=num%10;
		i++;
		num/=10;
	}

	if(isNegative) lcd_data('-', 250);

	// Display digits in the correct order
	for(j=i-1; j>=0; j--) {
		if(count==16) lcd_goto(2, 1);
		if(count==32) {
				lcd_cmd(0x01, 500);   // Clear display
				count=0;
		}
		lcd_data(arr[j]+'0', 250);
	}
}

// Send a nibble during LCD initialization
void lcd_nibble(unsigned char x, int n) {
    P3 = (x & 0xF0) | 0x08;
    delay(n);
}

// Initialize LCD in 4-bit mode
void lcd_init() {
	lcd_nibble(0x03, 30);
	lcd_nibble(0x03, 30);
	lcd_nibble(0x03, 30);
	lcd_nibble(0x20, 30);
	
	// Function Set: 4-bit mode
	lcd_cmd(0x20, 250);
	
	// Display ON, cursor ON, cursor blinking
	lcd_cmd(0x0F, 250);

	// Entry mode: increment cursor position
	lcd_cmd(0x06, 250);
	
	// Clear Display
	lcd_cmd(0x01, 500);
}

void main() {
	char str1[]="LCD testing...";
	char str2[]="Hello Dinesh Sir :)";

	lcd_init();

	while(1) {
		lcd_puts(str1);
		lcd_cmd(0x01, 500);
		count=0;

		lcd_puts(str2);
		delay(500);

		lcd_cmd(0x01, 500);
		count=0;
	}
}