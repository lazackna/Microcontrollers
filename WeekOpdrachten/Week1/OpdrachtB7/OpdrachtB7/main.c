/*
 * main.c
 *
 * Created: 2/2/2022 2:55:32 PM
 *  Author: User
 */ 

#define F_CPU 8e6

#define n 12

#include <xc.h>

#include <util/delay.h>

void setCharliePlexingLed(int lednr);

struct Signal // Struct for Signal information.
{
	char pin;
	int delay;
};

struct Signal signals[n]; // Struct for holding an array of Signals.

void createSignals();

void wait (int ms)
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	createSignals();
	int arraySize = sizeof(signals)/sizeof(signals[0]);
	while (1)
	{
		for (int i = 0; i < arraySize; i++)
		{
			setCharliePlexingLed(signals[i].pin);
			wait(signals[i].delay);
		}
		
	}
}

void setCharliePlexingLed(int lednr) {
	switch(lednr) {
		case 0:
		DDRA = 0b011;
		PORTA = 0b001;
		break;
		case 1:
		DDRA = 0b011;
		PORTA = 0b010;
		break;
		case 2:
		DDRA = 0b110;
		PORTA = 0b010;
		break;
		case 3:
		DDRA = 0b110;
		PORTA = 0b100;
		break;
		case 4:
		DDRA = 0b101;
		PORTA = 0b100;
		break;
		case 5:
		DDRA = 0b101;
		PORTA = 0b001;
		break;
	}
}

void createSignals() {
	for (int i = 0; i < 6; i++)
	{
		signals[i].pin = i;
		signals[i].delay = 200;
	}
	for (int i = 0; i < 6; i++) {
		signals[i + 5].pin = 5 - i;
		signals[i + 5].delay = 200;
	}
}