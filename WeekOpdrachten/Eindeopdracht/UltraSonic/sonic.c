///*
 //* UltraSonic.c
 //*
 //* Created: 2/23/2022 2:01:47 PM
 //* Author : User
 //*/ 
//
//#define F_CPU 8e6
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include <avr/interrupt.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include "lcd.h"
//#define BIT(x)			(1 << (x))
//void wait( int ms ) {
	//for (int i=0; i<ms; i++) {
		//_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	//}
//}
//
//ISR( INT1_vect ) {
	//PORTC = 0xff;
	//TCCR2 = 0b00001010;
//}
//
//ISR( INT2_vect ) {
	//PORTC = 0x0;
	//TCCR2 = 0b00001010;
//}
//
//
//void init_timer() {
	//OCR1A = 1;
	//TIMSK |= 0b1000;
	//TCCR1A = 0b10;
	//TCCR1B = 0b00001100;
//}
//
//void timer2Init(void) {
	//TCNT2 = -1; // This is inaccurate. actual value should be 7.812,5.
	//TIMSK |= BIT(7);
	//sei();
	//TCCR2 = 0b00001010;
//
//}
//volatile long long count = 0;
//ISR (TIMER2_COMP_vect ) {
	//count++;
	//PORTE ^= 1;
//}
//
//int main(void)
//{
	//DDRC = 0xFF; // Set all pins on DDRC to output.
	//DDRA = 0xFF;
	//EICRA |= 0b00101100; // Set PIN1 and PIN2 to rising edge.
	//EIMSK |= 0b0110; // Enable PIN1 and PIN2.
	//
	//sei(); // Enable global interrupt system
	//PORTE = 0b1; // Set pin 1 to high to have a starting bit.
	//timer2Init();
	//init_4bits_mode();
	//char * str = malloc(sizeof(char));
	//while(1) {
		////PORTA = 0b1;
		////wait(1);
		////PORTA = 0b0;
		//sprintf(str, "%llu", count);
		//wait(200);
		//lcd_write_string(str);
	//}
	//return 1;
//}
//
/*
 * Ultrasonic sensor HC-05 interfacing with AVR ATmega16
 * http://www.electronicwings.com
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define BIT(x)	(1 << (x))

#define  Trigger_pin	0	/* Trigger pin */
long int TimerOverflow = 0;

unsigned long cm = 0;

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
	cm = value;
}

ISR ( TIMER2_OVF_vect ) {
	TimerOverflow+= 1;
	TCNT2 = 0;
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void timer2Init(void) {
	TIMSK |= 0b01000000; // Enable overflow interupt.
	sei();
	TCCR2 = 0b0000;
}
char test = 0;
int main(void)
{
	text = malloc(sizeof(char) * 255);
	DDRA = 0b01;
	DDRB = 0xFF;
	
	EICRB |= 0b10110000; // set PE 6 and 7 to rising and falling respectively
	EIMSK |= 0b11000000; // enable pins 6 and 7.
	timer2Init();
	//sei();
	init_4bits_mode();
	reset();
	set_cursor(0);
	//lcd_write_string("hello");
	//PORTA = 0xff;
		
	while(1)
	{
		PORTA = 0b1;
		//wait(1);
		_delay_us(10);
		PORTA = 0;
		
		reset();
		sprintf(text, "%lu", cm);
		lcd_write_string(text);
		wait(1000);
		//isReading = true;
		//wait(1000);
		
		//while(!(PINA & BIT(1)));
		//break;
		//// The pin went high, start the timer.
		//TCCR2 |= 0b010;
		//TCNT2 = -1;
		////printf("test");
		//while(PINA & BIT(1));
		//// The pin went low, stop the timer.
		//TCCR2 &= 0b11111000;
		//unsigned long test = count;
		//count = 0;
		//sprintf(text, "%lu", test);
		////lcd_write_string(text);
		//fullCount = 0;
		//wait(1000);
		//fullCount = 0;
	}
	
}