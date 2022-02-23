
/*
 * lcdTest.c
 *
 * Created: 2/23/2022 10:15:48 AM
 *  Author: User
 */ 

#include "lcd.h"

int main(void)
{
	DDRD = 0xFF;
	init_4bits_mode();
	reset();
	set_cursor(4);
	lcd_write_string("David");
}