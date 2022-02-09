/*
 * main.c
 *
 * Created: 2/9/2022 10:53:26 AM
 *  Author: User
 */ 
#define F_CPU 8e6
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR( INT1_vect ) {
	char val = PINC; // Read the current values of PORTC.
	if(val == 0x1){	 // If value is 0x1 then reset the light to 0x80.
		PORTC = 0x80;
		}else{
		PORTC = 0; // Set the port to 0.
		PORTC |= (val >> 1); // Bit shift the current value one to the right and or it with the current values of PORTC.
	}
}

ISR( INT2_vect ) {
	char val = PINC; // Read the current values of PORTC.
	if(val == 0x80){ // If value is 0x80 then reset the light to 0x1.
		PORTC = 0x1;
	}else{
		PORTC = 0x0; // Set the port to 0.
		PORTC |= (val << 0x1); // Bit shift the current value one to the left and or it with the current values of PORTC.
	}	
}

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRC = 0xFF; // Set all pins on DDRC to output.
	
	EICRA |= 0b00111100; // Set PIN1 and PIN2 to rising edge.
	EIMSK |= 0b0110; // Enable PIN1 and PIN2.
	
	sei(); // Enable global interrupt system
	PORTC = 0b1; // Set pin 1 to high to have a starting bit.
	
    while(1)
    {
        wait(500); // Wait here. The main does nothing.
    }
	
	return 1;
}