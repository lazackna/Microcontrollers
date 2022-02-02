/*
 * main.c
 *
 * Created: 2/2/2022 1:07:47 PM
 *  Author: User
 */ 

#define F_CPU 8e6

#include <xc.h>

#include <util/delay.h>

#define n 16

void wait (int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}


struct Signal // Struct for Signal information.
{
	char pin;
	int delay;	
};

struct Signal signals[n]; // Struct for holding an array of Signals.

void createSignals();

int main(void)
{	
	
	DDRD = 0xff; // Set all pins to output.
	
	createSignals(); // Create the signal array.
	int arraySize = sizeof(signals)/sizeof(signals[0]); // Get the number of items in the array.
	while(1)
	{
		for (int i = 0; i < arraySize; i++)
		{
			PORTD = signals[i].pin; // Write to pin signals[i].pin.
			wait(signals[i].delay); // Wait for signals[i].delay ms.
		}
	}
}

void createSignals() {
	int pin = 0x1;
	signals[0].pin = pin;
	signals[0].delay = 50;
	for (int i = 1; i < 8; i++) { // Create lightstroke.
		signals[i].delay = 50;
		pin = pin << 1;
		signals[i].pin = pin;
	}
	
	for (int i = 9; i < 12; i = i + 2) // Create light flash.
	{
		signals[i].delay = 100;
		signals[i].pin = 0xff;
		signals[i + 1].delay = 100;
		signals[i + 1].pin = 0x0;
	}
	
}


