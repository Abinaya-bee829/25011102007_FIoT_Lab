#include <stdio.h>
#include <reg51.h>

sbit ledpin = P1^0;

void delay()
{
    unsigned char i;

    for(i = 0; i < 255; i++);
}

void main()
{
    while(1)
    {
        ledpin = 1;
        delay();
				delay();
        ledpin = 0;
        delay();
				delay();
    }
}