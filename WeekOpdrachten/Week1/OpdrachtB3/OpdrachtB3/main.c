/*
 * main.c
 *
 * Created: 2/2/2022 12:05:59 PM
 *  Author: User
 */ 

#define F_CPU 8e6

#include <xc.h>

#include <util/delay.h>

void wait (int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0x80; // Pin 7 is output
	PORTC = 0xFE; // Set PORTC pin 1 to input
    while(1)
    {
        if (PINC == 0b1)
        {
			PORTD = 0b00000000; // Turn of all the pins.
			wait(500);
			PORTD = 0b10000000; // Turn on pin 7
			wait(500);
        } else {
			PORTD = 0b00000000; // Turn of the led if button is not pressed
		}
    }
}