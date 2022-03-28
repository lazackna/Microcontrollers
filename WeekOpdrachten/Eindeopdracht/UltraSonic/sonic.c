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

#define  Trigger_pin	PA0

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

char * text;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

char test = 0;
int main(void)
{
	char string[10];
	long count;
	double distance;
	DDRA = 0x01;
	PORTD = 0xFF;
	DDRB = 0xFF;
	// We use timer 1.
	// To read high we set TCCR1B to rising edge.
	// Clear the Input Capture Flag (ICP).
	// This says if an interupt happened.
	init_4bits_mode();
	sei();
	TIMSK = (1 << TOIE1); // enable the timer1 overflow interrupt. 
	TCCR1A = 0;
	PORTB = 0;
	PORTA |= (1 << Trigger_pin);
	wait(1);
	PORTA &= (~(1 << Trigger_pin));
	
	while ((TIFR & (1 << ICF1)) == 0);
	
	PORTC = 0xFF;
	//while(1)
	//{
		//PORTA |= (1 << Trigger_pin);
		//_delay_us(10);
		//PORTA &= (~(1 << Trigger_pin));
		//
		//TCNT1 = 0;
		//TCCR1B = 0x41;
		//TIFR = 1<<ICF1;
		//TIFR = 1<<TOV1;
	//
		//while ((TIFR & (1 << ICF1)) == 0); // Wait for rising edge.
		//TCNT1 = 0;	/* Clear Timer counter */
		//TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		//TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		//TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
		//TimerOverflow = 0;/* Clear Timer overflow count */
//
		//while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
		//count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		///* 8MHz Timer freq, sound speed =343 m/s */
		//distance = (double)count / 466.47;
		//dtostrf(distance, 2, 2, text);
		//strcat(text, " cm    ");
		//reset();
		//lcd_write_string("Dest");
		//
		//wait(200);
	//}
	
}