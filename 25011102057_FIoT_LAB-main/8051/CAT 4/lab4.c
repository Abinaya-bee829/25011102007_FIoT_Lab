#include <reg51.h>

/* ---------------- Pin Definitions ---------------- */

// Matrix Keypad Connections (Rows and Columns)
sbit button_7 = P2^7;
sbit button_6 = P2^6;
sbit button_5 = P2^5;
sbit button_4 = P2^4;
sbit button_3 = P2^3;
sbit button_2 = P2^2;
sbit button_1 = P2^1;
sbit button_0 = P2^0;

// Decimal Point of Seven Segment Display
sbit DP = P0^7;

// LED Connections
sbit led1 = P3^0;
sbit led2 = P3^1;
sbit led3 = P3^2;
sbit led4 = P3^3;

// Stores the currently pressed key (10 = No key pressed)
unsigned char key = 10;


/* ---------------- Function Prototypes ---------------- */

void delay(void);
void keypad_scan(void);
void display_digit(void);
void led_control(void);
void running_led(void);
void alternative_led(void);
void binary_counter(void);
void blink_all(void);
void led_off(void);


/* -------------------------------------------------------
   Delay Function

   Creates a software delay while continuously scanning
   the keypad. If a new key is detected during the delay,
   the function exits immediately, allowing instant mode
   switching.
--------------------------------------------------------*/
void delay(void)
{
    int i, j;

    for(i = 0; i < 125; i++)
    {
        for(j = 0; j < 125; j++)
        {
            unsigned char temp = key;

            keypad_scan();

            if(key != temp)
                return;
        }
    }
}


/* -------------------------------------------------------
   Keypad Scan Function

   Scans the matrix keypad row by row and identifies the
   pressed key (0-9).
--------------------------------------------------------*/
void keypad_scan(void)
{
    unsigned char newkey = 10;

    // Scan First Row
    button_7 = 0;
    button_6 = 1;
    button_5 = 1;

    button_3 = 1;
    button_2 = 1;
    button_1 = 1;
    button_0 = 1;

    if(button_3 == 0)
        key = '1';
    else if(button_2 == 0)
        key = '2';
    else if(button_1 == 0)
        key = '3';
    else if(button_0 == 0)
        key = '4';

    // Scan Second Row
    if(newkey == 10)
    {
        button_7 = 1;
        button_6 = 0;
        button_5 = 1;

        if(button_3 == 0)
            key = '5';
        else if(button_2 == 0)
            key = '6';
        else if(button_1 == 0)
            key = '7';
        else if(button_0 == 0)
            key = '8';
    }

    // Scan Third Row
    if(newkey == 10)
    {
        button_7 = 1;
        button_6 = 1;
        button_5 = 0;

        if(button_3 == 0)
            key = '9';
        else if(button_2 == 0)
            key = '0';
    }

    // Update current key if a valid key is detected
    if(newkey != 10)
        newkey = key;
}


/* -------------------------------------------------------
   Seven Segment Display Function

   Displays the pressed digit (0-9) on the seven segment
   display.
--------------------------------------------------------*/
void display_digit(void)
{
    if(key == '0') { P0 = 0x3F; return; }
    if(key == '1') { P0 = 0x06; return; }
    if(key == '2') { P0 = 0x5B; return; }
    if(key == '3') { P0 = 0x4F; return; }
    if(key == '4') { P0 = 0x66; return; }
    if(key == '5') { P0 = 0x6D; return; }
    if(key == '6') { P0 = 0x7D; return; }
    if(key == '7') { P0 = 0x07; return; }
    if(key == '8') { P0 = 0x7F; return; }
    if(key == '9') { P0 = 0x6F; return; }
}


/* -------------------------------------------------------
   Individual LED Control (Keys 1-4)

   Turns ON the corresponding LED while turning OFF the
   remaining LEDs.
--------------------------------------------------------*/
void led_control(void)
{
    if(key == '1')
    {
        led1 = 1;
        led2 = led3 = led4 = 0;
        delay();
        if(key != '1') return;
    }

    else if(key == '2')
    {
        led2 = 1;
        led1 = led3 = led4 = 0;
        delay();
        if(key != '2') return;
    }

    else if(key == '3')
    {
        led3 = 1;
        led1 = led2 = led4 = 0;
        delay();
        if(key != '3') return;
    }

    else if(key == '4')
    {
        led4 = 1;
        led1 = led2 = led3 = 0;
        delay();
        if(key != '4') return;
    }
}


/* -------------------------------------------------------
   Running LED Pattern (Key 5)

   LEDs glow one after another in sequence until another
   key is pressed.
--------------------------------------------------------*/
void running_led(void)
{
    while(key == '5')
    {
        led2 = led3 = led4 = 0;
        led1 = 1;
        delay();
        if(key != '5') break;

        led1 = led3 = led4 = 0;
        led2 = 1;
        delay();
        if(key != '5') break;

        led2 = led1 = led4 = 0;
        led3 = 1;
        delay();
        if(key != '5') break;

        led2 = led3 = led1 = 0;
        led4 = 1;
        delay();
        if(key != '5') break;
    }
}


/* -------------------------------------------------------
   Alternate LED Pattern (Key 6)

   Alternates between LED pairs (1 & 3) and (2 & 4).
--------------------------------------------------------*/
void alternative_led(void)
{
    while(key == '6')
    {
        led1 = led3 = 0;
        led2 = led4 = 1;
        delay();
        if(key != '6') break;

        led1 = led3 = 1;
        led2 = led4 = 0;
        delay();
        if(key != '6') break;
    }
}


/* -------------------------------------------------------
   Binary Counter (Key 7)

   Displays binary count from 0 to 15 using four LEDs.
--------------------------------------------------------*/
void binary_counter(void)
{
    while(key == '7')
    {
        int i;

        for(i = 0; i < 16; i++)
        {
            P3 = i;
            delay();

            if(key != '7')
                return;
        }
    }
}


/* -------------------------------------------------------
   Blink All LEDs (Key 8)

   Turns all LEDs ON and OFF repeatedly.
--------------------------------------------------------*/
void blink_all(void)
{
    while(key == '8')
    {
        led1 = led2 = led3 = led4 = 1;
        delay();
        if(key != '8') return;

        led1 = led2 = led3 = led4 = 0;
        delay();
        if(key != '8') return;
    }
}


/* -------------------------------------------------------
   LED OFF Mode (Key 9)

   Turns OFF all LEDs until another key is pressed.
--------------------------------------------------------*/
void led_off(void)
{
    while(key == '9')
    {
        led1 = led2 = led3 = led4 = 0;
        delay();

        if(key != '9')
            return;
    }
}


/* -------------------------------------------------------
   Main Function

   Continuously scans the keypad, displays the pressed
   digit on the seven segment display and executes the
   corresponding LED mode.
--------------------------------------------------------*/
void main(void)
{
    // Initialize LEDs and Seven Segment Display
    led1 = led2 = led3 = led4 = 0;
    P0 = 0;

    while(1)
    {
        // Wait until a valid key is pressed
        while(key == 10)
        {
            keypad_scan();
        }

        // Display the pressed key
        display_digit();

        // Execute the selected mode
        switch(key)
        {
            case '1':
                led_control();
                break;

            case '2':
                led_control();
                break;

            case '3':
                led_control();
                break;

            case '4':
                led_control();
                break;

            case '5':
                running_led();
                break;

            case '6':
                alternative_led();
                break;

            case '7':
                binary_counter();
                break;

            case '8':
                blink_all();
                break;

            case '9':
                led_off();
                break;

            case '0':
                key = 10;
                led1 = led2 = led3 = led4 = 0;
                P0 = 0x3F;
                break;

            default:
                break;
        }
    }
}