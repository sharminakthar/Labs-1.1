/*avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -Wl,-u,vfprintf -lprintf_flt -lm  c63.c -o c63.elf 
 *avr-objcopy -O ihex c63.elf c63.hex
 *avrdude -c usbasp -p m644p -U flash:w:c63.hex
 */
#include <avr/io.h>
#include <util/delay.h>

int main(){
const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};
int x=0;
DDRA = 0xFF
DDRC = 0x00;
PORTC |=_BV(7);
for(;;){
if(!(PINC &_BV(7)){
x++;
x %=10;
}
PORTA = segments[x];
}

 