#include <reg51.h>

sbit E=P3^3;        // LCD Enable pin
sbit ROW7=P2^7;     // Keypad row 7
sbit ROW6=P2^6;     // Keypad row 6
sbit UP=P2^2;       // Up key
sbit DOWN=P2^2;     // Down key
sbit LEFT=P2^3;     // Left key
sbit RIGHT=P2^1;    // Right key

int row=1;          // Current LCD row
int col=1;          // Current LCD column

// Software delay for LCD and keypad timing
void delay(int n) {
	int i;
	int j;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
		}
	}
	E=0;              // Disable LCD
}

// Send an LCD command in 4-bit mode
void lcd_cmd(unsigned char cmd, int n) {
	P3=(cmd & 0xF0) | 0x08;   // Send upper nibble with RS=0
	delay(n);
	P3=(cmd<<4) |0x08;        // Send lower nibble with RS=0
	delay(n);
}

// Send character data to the LCD
void lcd_data(unsigned char ch, int n) {
	P3=(ch & 0xF0) | 0x0C;    // Send upper nibble with RS=1
	delay(n);
	P3=(ch<<4) |0x0C;          // Send lower nibble with RS=1
	delay(n);
}

// Move LCD cursor to the specified row and column
void lcd_goto(char row, char col) {
	char address;
	if(row==1) {
		address=0x00+col-1;
	}
	else if(row==2) {
		address=0x40+col-1;
	}
	else return;
	
	lcd_cmd(0x80 | address, 50);   // Set DDRAM address
}

// Send a nibble during LCD initialization
void lcd_nibble(unsigned char x, int n) {
    P3 = (x & 0xF0) | 0x08;
    delay(n);
}

// Initialize the LCD in 4-bit mode
void lcd_init() {
	lcd_nibble(0x03, 30);
	lcd_nibble(0x03, 30);
	lcd_nibble(0x03, 30);
	lcd_nibble(0x20, 30);
	
	// Function Set: 4-bit mode
	lcd_cmd(0x28, 50);
	
	// Display ON, cursor ON, blinking
	lcd_cmd(0x0F, 50);

	// Entry mode: increment cursor position
	lcd_cmd(0x06, 50);
	
	// Clear display
	lcd_cmd(0x01, 100);
}

// Move character one position upward
void move_up() {
		if(row==1) return;
		
		lcd_goto(row, col);
		lcd_data(' ', 5);       // Erase current position
		
		--row;
		
		lcd_goto(row, col);
		lcd_data('A', 5);       // Display character at new position
}

// Move character one position to the left
void move_left() {
		if(col==1) return;
		
		lcd_goto(row, col);
		lcd_data(' ', 5);       // Erase current position
		
		--col;
		
		lcd_goto(row, col);
		lcd_data('A', 5);       // Display character at new position
}

// Move character one position downward
void move_down() {
		if(row==2) return;
		
		lcd_goto(row, col);
		lcd_data(' ', 5);       // Erase current position
		
		++row;
		
		lcd_goto(row, col);
		lcd_data('A', 5);       // Display character at new position
}

// Move character one position to the right
void move_right() {
		if(col==16) return;
		
		lcd_goto(row, col);
		lcd_data(' ', 5);       // Erase current position
		
		++col;
		
		lcd_goto(row, col);
		lcd_data('A', 5);       // Display character at new position
}

// Scan keypad and return the corresponding key number
int keypad_scan() {
	UP=DOWN=0;
	LEFT=RIGHT=1;
	
	ROW7=1;
	ROW6=1;
	
	// Check UP and DOWN keys
	if(ROW7==0) {
		delay(10);
		if(ROW7==0) {
			while(!ROW7);
				return 1;
		}
	}
	
	if(ROW6==0) {
		delay(10);
		if(ROW6==0) {
			while(!ROW6);
				return 2;
		}
	}
	
	// Check LEFT key
	LEFT=0;
	UP=DOWN=RIGHT=1;
	ROW7=1;
	ROW6=1;
	
	if(ROW6==0) {
		delay(10);
		if(ROW6==0) {
			while(!ROW6);
				return 3;
		}
	}
	
	// Check RIGHT key
	RIGHT=0;
	UP=DOWN=LEFT=1;
	ROW7=1;
	ROW6=1;
	
	if(ROW6==0) {
		delay(10);
		if(ROW6==0) {
			while(!ROW6);
				return 4;
		}
	}
	
	return 0;       // No key pressed
}

void main() {
	int key;
	unsigned char a='A';

	lcd_init();

	// Display character A at the initial position
	lcd_goto(1, 1);
	lcd_data(a, 10);

	while(1) {
		key=keypad_scan();
		
		if(key!=0) {
			switch(key) {
				case 1:
					move_up();
					break;
				case 2:
					move_down();
					break;
				case 3:
					move_left();
					break;
				case 4:
					move_right();
					break;
				case 0:
					break;
			}
		}
	}
}