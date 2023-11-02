/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_adc(void)
{
ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADEN); // F_CPU/64
}

void channel_adc(uint8_t n)
{
ADMUX = n;
}

uint16_t read_adc(void)
{
ADCSRA |= _BV(ADSC) | _BV(ADEN);

while(ADCSRA & _BV(ADSC))
; // wait

return ADC;
}

int main(void)
{
DDRB |= _BV(7);


channel_adc(1);
init_debug_uart0();
init_adc();

for/*ever*/(;;)
{
if(read_adc() < 899)
PORTB |= _BV(7);
else
PORTB &= ~_BV(7);
_delay_ms(200);
}

/*
result = read_adc();
voltage = ((double)result/1024) * 3.3;

printf("%4d : %6.5fV\n", result, voltage);
_delay_ms(1000);
*/
}

