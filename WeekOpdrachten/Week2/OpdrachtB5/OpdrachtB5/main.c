/*
 * main.c
 *
 * Created: 2/9/2022 2:11:36 PM
 *  Author: User
 */ 

#define lcdPort PORTC

#define RS 2
#define EN 3

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void lcd_command ( unsigned char dat );
void lcd_en(void);
void init_4bits_mode(void);
void lcd_write_string(const char *str);
void lcd_write_data(unsigned char byte);
void reset(void);
void set_cursor(int position);

int main(void)
{
	DDRD = 0xFF;
    init_4bits_mode();
	//char *str = "roof";
	reset();
	set_cursor(4);
	lcd_write_string("David");
	

	
}

void set_cursor(int position){
	lcd_command((0x80 + position));
}

void lcd_write_string(const char *str) {

	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<RS);
	lcd_en();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<RS);
	lcd_en();
}

void init_4bits_mode(void) {
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
	PORTC = 0xF0; // Lcd, blink and cursor on.
	lcd_en();

	// Step 4 (table 12)
	PORTC = 0x00;  
	lcd_en();
	PORTC = 0x60; // Increase cursor position.
	lcd_en();

}

void reset(void){
	
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
	PORTC |= (1<<EN);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<EN);  	// E low
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
