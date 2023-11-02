#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// interrupt routine
ISR(ADC_vect){
PINB |= _BV(7);
}

void init_adc(void)
{
// free running mode
ADCSRA |= _BV(ADATE) | _BV(ADEN) | _BV(ADSC) | _BV(ADIE);

//ADCSRB = 0x00;
}

void channel_adc(uint8_t n)
{
ADMUX = n;
}

int main(void)
{

DDRB |= _BV(7);
init_adc();
channel_adc(1);


// adc prescaler 64
//ADCSRA = _BV(ADPS2) | _BV(ADPS1);


// start interrupts
sei();

while(1)
;
}
