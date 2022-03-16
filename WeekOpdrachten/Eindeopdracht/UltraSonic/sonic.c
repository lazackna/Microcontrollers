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

#define  Trigger_pin	PA0	/* Trigger pin 

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
//}
bool isReading = false;
long long count = 0;
long long fullCount = 0;
char * text;
ISR ( INT6_vect ) {
	TCCR2 |= 0b010;
	PORTB = 2;
}


ISR ( INT7_vect ) {
	PORTB = 0;
	TCCR2 &= 0b11111000;
	TCNT2 = -58;
	fullCount = count;
	count = 0;
	isReading = false;
	sprintf(text, "Distance: %d", fullCount);
	reset();
	lcd_write_string(text);
	fullCount = 0;
}

ISR ( TIMER2_COMP_vect ) {
	count++;
	//TCNT2 = -8;
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void timer2Init(void) {
	TCNT2 = -58;
	TIMSK |= 0b10000000;
	sei();
	TCCR2 = 0b1000;
}
char test = 0;
int main(void)
{
	text = malloc(sizeof(char) * 255);
	DDRA = 0b00000010;
	DDRB = 0xFF;
	
	//EICRB |= 0b10110000; // set PE 6 and 7 to rising and falling respectively
	//EIMSK |= 0b11000000; // enable pins 6 and 7.
	timer2Init();
	//sei();
	init_4bits_mode();
	//lcd_write_string("hello");
	while(1)
	{
		PORTA |= 1;
		
		wait(1);
		_delay_us(15);
		PORTA &= h;
		//isReading = true;
			
		while(!(PINA & BIT(2)));
		// The pin went high, start the timer.
		printf("test");
		while(PINA & BIT(2)) {
			
		}
		// The pin went high, stop the timer.
	
		
		wait(1);
	}
}