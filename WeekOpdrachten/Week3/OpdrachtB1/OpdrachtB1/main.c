/*
 * OpdrachtB1.c
 *
 * Created: 2/16/2022 10:08:09 AM
 * Author : User
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"

#define  BIT(x) (1 << (x))

volatile int TimerPreset = -1;
volatile int val = 0;
volatile int write = 0;
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

ISR( TIMER2_OVF_vect ) {
	TCNT2 = TimerPreset;
	val++;
	reset();
	char * str = malloc((sizeof(char) * 3));
	sprintf(str, "%d", val);
	lcd_write_string(str);
	free(str);
}

void timer2Init(void) {
	TCNT2 = TimerPreset;
	TIMSK |= BIT(6);
	sei();
	TCCR2 = 0b00000111;
}

int main(void)
{
	DDRD &= ~BIT(7);
	DDRA = 0xFF;
	DDRB = 0xFF;
	init_4bits_mode();
	reset();
	timer2Init();
	while (1)
	{
		PORTA = TCNT2;
		PORTB = val;
		wait(10);
	}
}

