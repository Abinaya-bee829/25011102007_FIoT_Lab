#include <reg51.h>

// LED connections
sbit led1 = P3^0;
sbit led2 = P3^1;
sbit led3 = P3^2;
sbit led4 = P3^3;

// Push button connections
// P2.7 is driven HIGH and P2.3 is used to detect the button press
sbit button_1 = P2^7;
sbit button_2 = P2^3;

// Stores the current mode (0-3)
int count = 0;

// Delay function with button polling
// If the button is pressed during the delay, switch to the next mode
void delay()
{
    int i, j;

    for(i = 0; i < 500; i++)
    {
        for(j = 0; j < 500; j++)
        {
            // Detect button press (active LOW)
            if(button_2 == 0)
            {
                // Switch to the next mode
                count++;
                count %= 4;

                // Wait until the button is released
                while(!button_2) {}

                // Exit immediately so the current mode stops
                return;
            }
        }
    }
}

// Mode 0 - Running LED
void mode_0()
{
    while(count == 0)
    {
        // Turn ON LED1
        led2 = led3 = led4 = 0;
        led1 = 1;
        delay();
        if(count != 0) break;

        // Turn ON LED2
        led1 = led3 = led4 = 0;
        led2 = 1;
        delay();
        if(count != 0) break;

        // Turn ON LED3
        led2 = led1 = led4 = 0;
        led3 = 1;
        delay();
        if(count != 0) break;

        // Turn ON LED4
        led2 = led3 = led1 = 0;
        led4 = 1;
        delay();
    }
}

// Mode 1 - 4-bit Binary Counter
void mode_1()
{
    while(count == 1)
    {
        int i;

        // Display binary numbers from 0 to 15
        for(i = 0; i < 16; i++)
        {
            P3 = i;
            delay();

            // Exit immediately if the mode changes
            if(count != 1)
                return;
        }
    }
}

// Mode 2 - Alternate LEDs
void mode_2()
{
    while(count == 2)
    {
        // LED2 and LED4 ON
        led1 = led3 = 0;
        led2 = led4 = 1;
        delay();
        if(count != 2) break;

        // LED1 and LED3 ON
        led1 = led3 = 1;
        led2 = led4 = 0;
        delay();
    }
}

// Mode 3 - All LEDs Blink
void mode_3()
{
    while(count == 3)
    {
        // Turn all LEDs ON
        led1 = led2 = led3 = led4 = 1;
        delay();
        if(count != 3) break;

        // Turn all LEDs OFF
        led1 = led2 = led3 = led4 = 0;
        delay();
    }
}

void main()
{
    // Initialize keypad lines
		// P2.7 drives the keypad row and P2.3 is monitored for button detection
    button_1 = 0;
    button_2 = 1;

    // Continuously execute the selected mode
    while(1)
    {
        switch(count)
        {
            case 0:
                mode_0();
                break;

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