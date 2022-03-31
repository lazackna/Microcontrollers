#ifndef LCD_H
#define LCD_H

#define LCD_RS 2
#define LCD_EN 3

#ifndef F_CPU
#define F_CPU 8e6
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LCD_MAX_CHARACTERS 20

void lcd_command ( unsigned char dat );
void lcd_en(void);
void lcd_init_4bits_mode(void);
void lcd_write_string(const char *str);
void lcd_write_data(unsigned char byte);
void lcd_reset(void);
void set_cursor(int position);

#endif /* LCD_H */