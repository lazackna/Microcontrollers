#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
	ADMUX = 0b01100011;			// AREF=VCC, result left adjusted, channel3 at pin PF3
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no start, no free running, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	adcInit();					// initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);
		while (ADCSRA & BIT(6));
		PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
	}
}


