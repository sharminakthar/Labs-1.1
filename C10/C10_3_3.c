#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t i = 0;

// interrupt routine 1
ISR(INT1_vect)
{
if (i != 255)
i++;
PORTC = i;
}

ISR(INT0_vect)
{
if(i != 0)
i++;
PORTC = i;
}

int main(void)
{

EICRA |= _BV(ISC01) | _BV(ISC00);
// enable interrupt
EIMSK |= _BV(INT0) | _BV(INT1);
DDRC = 0xFF;

sei();
PORTC = i;
while(i)
;
}


