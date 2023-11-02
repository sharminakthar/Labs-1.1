//avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -c user_input.c -o user_input.o
//avr-gcc -mmcu=atmega644p -L. -o user_input.elf user_input.o -llcd
//avr-objcopy -O ihex user_input.elf user_input.hex
//avrdude -c usbasp -p m644p -U flash:w:user_input.hex

#include "lcd.h"
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#define bar_height 3
#define bar_width 49
#define bar_oy 300
#define max_ox 239
#define SPEED 5

int main(void)
{
	DDRD = 0x00;
	PORTD |= _BV(0);
	DDRD &= ~_BV(0);  
	uint16_t x=94;//,bar_speed=0;
	int16_t a;
	int8_t way_x=0;
	a=x%SPEED;
	init_lcd();
	set_orientation(North);
	//rectangle bar = { x, x+bar_width, bar_oy, bar_oy+bar_height};
	//fill_rectangle(bar, GREEN);
	while(1)
	{
		if((!(PIND & 0x01)) && (PIND | 0x01))
		{
			way_x=0;
		}
		else
		{
			way_x=1;
		}
		clear_screen();
		rectangle bar = { x, x+bar_width, bar_oy, bar_oy+bar_height};
		fill_rectangle(bar, GREEN);
		if( x > a)
		{	
			if( way_x == 1)
			{
				if( x < (max_ox-a-bar_width)) x += SPEED;
				else 
				{
					x -= SPEED;
					way_x = -1;
				}
			}
			else
			{
				x = x - SPEED;
			}
		}
		else
		{
			x += SPEED;
			way_x = 1;
		}
		_delay_ms(40);
	}
}
