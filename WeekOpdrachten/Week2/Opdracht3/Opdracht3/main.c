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

void display(int digit);

char currentNumber = 0;


ISR( INT1_vect ) 
{
	currentNumber++;
	
	display(currentNumber);
}

ISR( INT2_vect ) 
{
	currentNumber--;
	
	display(currentNumber);
}

void wait( int ms ) 
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Numbers[17] = {
//	  Pgfedcba
	0b00111111,	// 0
	0b00000110,	// 1
	0b01011011,	// 2
	0b01001111,	// 3
	0b01100110,	// 4
	0b01101101,	// 5
	0b01111101,	// 6
	0b00000111,	// 7
	0b01111111,	// 8
	0b01101111,	// 9
	0b01110111,	// 10
	0b01111100,	// 11
	0b00111001,	// 12
	0b01011110,	// 13
	0b01111001,	// 14
	0b01110001,	// 15
	0b11111001	// Error
};

void display(int digit) 
{
	if (digit < 15 && digit >= 0)
		PORTA = Numbers[digit];
	else
		PORTA = Numbers[16];
}

int main(void)
{
	DDRA = 0xFF; // Set all pins on DDRC to output.
	
	EICRA |= 0b00111100; // Set PIN1 and PIN2 to rising edge.
	EIMSK |= 0b0110; // Enable PIN1 and PIN2.
	
	sei(); // Enable global interrupt system
	display(0);
	
	while(1)
	{
		wait(500); // Wait here. The main does nothing.
	}
	
	return 1;
}