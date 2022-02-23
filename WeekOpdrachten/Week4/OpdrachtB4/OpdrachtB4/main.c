#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b11100011;			// AREF=2.56V, result left adjusted, channel3 at pin PF3
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no start, no free running, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	adcInit();					// initialize ADC
	
	init_4bits_mode();
	char * str = malloc(sizeof(char));
	while (1)
	{
		ADCSRA |= BIT(6);
		while (ADCSRA & BIT(6));
		PORTA = ADCH;
		char i = ADCH;
		sprintf(str, "%d", i);
		lcd_write_string(str);
		wait(500);				// every 100 ms (busy waiting)
	}
	free(str);
}


