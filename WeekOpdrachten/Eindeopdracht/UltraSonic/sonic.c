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

int currentDistance = 0;

int timer2Overflow = 0;

char tickOnTrigger = 0;

ISR (INT7_vect ) {
	if(tickOnTrigger = 0) {
		tickOnTrigger = TCNT2;
	} else {
		
	}
}

ISR( TIMER2_OVF_vect ) {
	timer2Overflow++;
}

int main(void) {
	
	DDRD = 0xFF; // PORT D to output.
	
	DDRE = 0b00001111; //PORTE(7:4) input, PORTE(3:0) output.
	
	EICRB |= 0x40;
	EIMSK |= 0x80;
	
	init_4bits_mode();
	
	while(1) {
		PORTE |= (1 << Trigger_pin);
		_delay_us(10);
		
		PORTE &= ~(1 << Trigger_pin);
		
		char string[13];
		
		sprintf(string, "%d cm    ", )
	}
	
	return 1;
}