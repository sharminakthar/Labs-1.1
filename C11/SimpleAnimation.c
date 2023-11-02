//avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -c SimpleAnimation.c -o SimpleAnimation.o
//avr-gcc -mmcu=atmega644p -L. -o SimpleAnimation.elf SimpleAnimation.o -llcd
//avr-objcopy -O ihex SimpleAnimation.elf SimpleAnimation.hex
//avrdude -c usbasp -p m644p -U flash:w:SimpleAnimation.hex

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#define SPEED 10

int main(){
	init_lcd();
	uint16_t x=0, y=0;
	int16_t i=0, j=0;
	while(1){ //infinite loop
		//clear_screen();
		rectangle r = {x, x+5, y, y+5};
		fill_rectangle(r, YELLOW);
		x=x+i;
		y=y+j;
		if(x==0){
			i=SPEED; //causes a direction change on wall
		}
		if(x==240){
			i=-SPEED; //causes a direction change on wall
		}
		if(y==0){
			j=SPEED; //causes a direction change on wall
		}
		if(y==320){
			j=-SPEED; //causes a direction change on wall
		}
		_delay_ms(40);
		}
	return 0;
}