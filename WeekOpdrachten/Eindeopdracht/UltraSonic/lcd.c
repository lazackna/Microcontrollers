/*
 * main.c
 *
 * Created: 2/9/2022 2:11:36 PM
 *  Author: User
 */ 

#include "lcd.h"

void set_cursor(int position){
	lcd_command((0x80 + position));
}

void lcd_write_string(const char *str) {
	lcd_reset();
	set_cursor(0);
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_en();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_en();
}

void lcd_init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// Set lcd to 4-bit mode.
	lcd_en();

	// Step 3 (table 12)
	PORTC = 0x20;  
	lcd_en();
	PORTC = 0x80; // Set to 2 lines.
	lcd_en();

	// Step 4 (table 12)
	PORTC = 0x00;   
	lcd_en();
	PORTC = 0b11000000; // Cursor and blink off.
	lcd_en();

	// Step 4 (table 12)
	PORTC = 0x00;  
	lcd_en();
	PORTC = 0x60; // Increase cursor position.
	lcd_en();

}

void lcd_reset(void){
	
	PORTC = 0x00;
	lcd_en();
	PORTC = 0x01; 
	lcd_en();
	
	PORTC = 0x00;
	lcd_en();
	PORTC = 0x02;
	lcd_en();
}

void lcd_en(void) {
	PORTC |= (1<<LCD_EN);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_EN);  	// E low
	_delay_ms(1);
}

void lcd_command ( unsigned char dat ){
	PORTC = dat & 0xF0;			// hoge nibble
	PORTC |= 0x08;				// data (RS=0),									// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x04;					// stop (EN = 0)
	
	PORTC = (dat & 0x0F) << 4;	// lage nibble
	PORTC |= 0x08;				// data (RS=0),									// start (EN=1)
	_delay_ms(1);					// wait 1 ms
	PORTC = 0x00;					// stop (EN=0 RS=0)
}
