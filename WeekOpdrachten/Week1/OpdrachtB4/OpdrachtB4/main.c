/*
 * main.c
 *
 * Created: 2/2/2022 12:45:16 PM
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
	DDRD = 0xff; // Set all pins to output;
	char light = 0x1;
	while (1)
	{
		if (light == 0x80) {
			light = 0b1; // If the light is at 0b10000000 then set light t0 0b00000001.
		} else {
			light = light << 1; // Bit shift the light one to the left.
		}
		PORTD = light;
		wait(25);
	}
}