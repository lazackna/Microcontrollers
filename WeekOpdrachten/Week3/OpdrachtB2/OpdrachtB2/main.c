/*
 * OpdrachtB2.c
 *
 * Created: 2/16/2022 12:03:58 PM
 * Author : User
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

volatile int msCount = 0;
volatile int isOn = 0;
int on;
int off;
// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void timer2Init(void) {
	TCNT2 = -8; // This is inaccurate. actual value should be 7.812,5.
	TIMSK |= BIT(7);
	sei();
	TCCR2 = 0b00001101;

}

ISR (TIMER2_COMP_vect ) {
	msCount++;
	if (isOn) {
		//if (msCount == 15)
		//{
			PORTD = 0x00;
			//msCount = 0;
			TCNT2 = -off;
			isOn = 0;
		//}
	} else {
		//if (msCount == 25)
		//{
			PORTD = 0x80;
			TCNT2 = -on;
			//msCount = 0;
			isOn = 1;
		//}
	}

}

int main(void)
{
	on = 117; //7.8125 * 15;
	off = 195; //7.8125 * 25;

	DDRD = 0xFF;
	timer2Init();
    while (1)
    {
		wait(10);
    }
}

