#ifndef WAIT.H
#define

#include <util/delay.h>

void wait (int ms) 
{
		for (int i = 0; i < ms; i++)
		{
			_delay_ms(1);
		}
}
#endif