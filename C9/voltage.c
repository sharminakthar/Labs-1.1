/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *           View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 *avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -Wl,-u,vfprintf -lprintf_flt -lm  embedded_boost.c -o embedded_boost.elf
 *avr-objcopy -O ihex embedded_boost.elf embedded_boost.hex
 *avrdude -c usbasp -p m644p -U flash:w:embedded_boost.hex
 */
#include <avr/io.h>
#include <util/delay.h>
#include "debug.h"

void init_adc(void)
{
	ADMUX = 0x00;
	ADCSRA |= _BV(ADEN) |_BV(ADPS1)|_BV(ADPS2);
}

uint16_t read_adc(void)
{
	ADCSRA |=_BV(ADSC);
	while (ADCSRA &_BV(ADSC)){};
	return ADC;
}

int main(void)
{
	uint16_t result;
	double voltage;
	
	init_debug_uart0();
	init_adc();
	
	for (;;) 
	{
		result= read_adc();
		voltage= (3.3*result)/1024;
		printf("%4d : %6.5fV\n", result, voltage);
		_delay_ms(1000);
	}
}
