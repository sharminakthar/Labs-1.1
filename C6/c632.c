#include <avr/io.h>
#include <util/delay.h>

int main(){
const uint8_t segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};
int x=0;
DDRA = 0xFF
DDRC = 0x00;
PORTC |=_BV(7);
for(;;){
while ((PINC &_BV(7)) != 0);{
count++;
while ((PINC &_BV(7)) == 0);
}
PORTA = segments[x];
}

 


