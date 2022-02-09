/*
 * main.c
 *
 * Created: 2/9/2022 11:36:58 AM
 *  Author: User
 */ 

#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void displayNumber(char digit);

void wait( int ms ) 
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Numbers[8] = {
	0x01,
	0x02,
	0x40,
	0x10,
	0x08,
	0x04,
	0x40,
	0x20
};

void displayNumber(char digit) 
{
	PORTA = digit;
}

int main(void)
{
	DDRA = 0xFF; // Set all pins on DDRC to output.
	
	while(1)
	{
		for (int i = 0; i < (sizeof(Numbers) / sizeof(Numbers[0])); i++)
		{
			displayNumber(Numbers[i]);
			wait(100);
		}
	}
	
	return 1;
}