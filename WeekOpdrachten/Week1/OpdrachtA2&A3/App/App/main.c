/*
 * main.c
 *
 * Created: 2/2/2022 11:34:04 AM
 *  Author: User
 */ 

#include <xc.h>
#include <util/delay.h>


wait (int ms) 
{
		for (int i = 0; i < ms; i++)
		{
			_delay_ms(1);
		}
}

int main(void)
{
    DDRD = 0b11111111;			// All pins PORTD are set to output
    
    while (1) {
	    PORTD = 0xAA;			// Write 10101010b PORTD
	    wait( 1000 );
	    PORTD = 0x55;			// Write 01010101b PORTD
	    wait( 1000 );
    }

    return 1;
}