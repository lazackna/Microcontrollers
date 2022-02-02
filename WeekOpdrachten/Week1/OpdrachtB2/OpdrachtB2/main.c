/*
 * main.c
 *
 * Created: 2/2/2022 11:49:00 AM
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
	DDRD = 0b11111111;
	
    while(1)
    {
        PORTD = 0b10000000;
		wait(500);
		PORTD = 0b01000000;
		wait(500);
    }
}