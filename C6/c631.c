#include <avr/io.h>
#include <util/delay.h>

int main(){
const uint8_t segments[10] = {0xFC, 0x60, 0xDB, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};
int x=0;
DDRA = 0xFF;
for(;;){
x %=10;
PORTA = segments[x];
_delay_ms(1000);
x++;
}
}
