//avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -c SimpleGraphics.c -o SimpleGraphics.o
//avr-gcc -mmcu=atmega644p -L. -o SimpleGraphics.elf SimpleGraphics.o -llcd
//avr-objcopy -O ihex SimpleGraphics.elf SimpleGraphics.hex
//avrdude -c usbasp -p m644p -U flash:w:SimpleGraphics.hex

#include <avr/io.h>
#include "lcd.h"

int main(){
	init_lcd();
	rectangle r = {120, 130, 110, 120};
	fill_rectangle(r,YELLOW);
	return 0;
}