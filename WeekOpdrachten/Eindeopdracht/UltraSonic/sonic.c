#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "util.h"
#include "lcd.h"

#define BIT(x)	(1 << (x))
#define maxCm 60

#define  Trigger_pin 0 /* Trigger pin */
long int TimerOverflow = 0;

double cm = 0;

char * text;
ISR ( INT6_vect ) {
	TCNT2 = 0;	// Clear the timer register.
	TimerOverflow = 0;
	TCCR2 |= 0b001; // Start the timer with no prescaler.
}

ISR ( INT7_vect ) {
	TCCR2 &= 0b11111000;	// Stop the timer.
	long long int value = TCNT2 + (255 * TimerOverflow); // don't forget to add the current value in the timer.
	TCNT2 = 0;	// Clear the timer register.
	TimerOverflow = 0;
	double newCm = (double)value / 466.47;

	cm = newCm;
}

/************************************************************************/
/* Count the amount of overflows on timer2                                                                     */
/************************************************************************/
ISR ( TIMER2_OVF_vect ) {
	TimerOverflow+= 1;
	TCNT2 = 0;
}

/************************************************************************/
/* Turn a pin on/off on the compare of timer0.							*/
/************************************************************************/
char isOn = 0;
long long int timesCompare = 0;
ISR ( TIMER0_COMP_vect ) {
	if(cm > maxCm) return;
	if(timesCompare > (cm / 3)) {
		if(isOn) {
			isOn = 0;
			PORTB = 1;
		} else {
			PORTB = 0;
			isOn = 1;
		}
		timesCompare = 0;
	}
	timesCompare++;
}

/************************************************************************/
/* Initialize timer 2 which is used for an ultrasonic sensor.			*/
/************************************************************************/
void timer2Init(void) {
	TIMSK |= 0b01000000; // Enable overflow interupt.
	sei();
	TCCR2 = 0b0000;
}

/************************************************************************/
/* Initialize timer 0 which is used for buzzer.							*/
/************************************************************************/

void timer0Init(void){
	TCCR0 = 0b00001011; // Turn on CTC. Prescaler on 256.
	TIMSK |= BIT(1); // Set timer/counter 0 to compare match interupt. 31,250
	OCR0 = 100;
	DDRB |= 0x01; //set pin 1 on port B to output
}

int main(void)
{
	text = malloc(sizeof(char) * 255);
	DDRA = 0b01;
	wait(1);
	
	EICRB |= 0b10110000; // set PE 6 and 7 to rising and falling respectively
	EIMSK |= 0b11000000; // enable pins 6 and 7.
	timer2Init();
	timer0Init();
	lcd_init_4bits_mode();
	
	wait(200);	
	while(1)
	{
		PORTA = 0b1;
		_delay_us(10);
		PORTA = 0;
		int value = (int) cm;
		sprintf(text, "%d", value);
		lcd_write_string(text);
		wait(100);
	}
	
}