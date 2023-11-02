// *avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -Wl,-u,vfprintf -lprintf_flt -lm  HelloWorld.c -o HelloWorld.elf
//*avr-objcopy -O ihex HelloWorld.elf HelloWorld.hex 
//*avrdude -c usbasp -p m644p -U flash:w:HelloWorld.hex

#include "lcd.h"

int main(void){
	init_lcd();
	display_string("Hello World");
	
	return 0;
}