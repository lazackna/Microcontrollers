/*
 * main.c
 *
 * Created: 2/2/2022 1:51:29 PM
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

typedef enum {false,true} bool; // Creating or own boolean.

int main(void)
{
	DDRD = 0x80; // Set pin 7 to output, others to input.
	PORTC = 0xfe; // Set pin 1 to input. others to output.
	
	bool isFast = false;
	bool isHolding = false;
	
	while (1)
	{
		if (PINC == 0x1) { // Check if PINC.0 is pressed.
			if (isHolding == 0) {
				isFast = !isFast; // Change the cycle mode.
				isHolding = true; // Remember that the button is being pressed.
			}
		} else {
			isHolding = false; // Remember that button is no longer pressed.
		}
		
		PORTD = 0x80; // Turn on LED 7.
		if (isFast) {
			wait(125);
		} else {
			wait(500);
		}
		if (PINC == 0x1) {
			if (isHolding == 0) {
				isFast = !isFast;
				isHolding = true;
			}
		} else {
			isHolding = false;
		}
		
		PORTD = 0x0;
		if (isFast) {
			
			wait(125);
			} else {
			wait(500);
		}
	}
}