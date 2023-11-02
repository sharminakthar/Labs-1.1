#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
const uint8_t segments[10] = {0xFC, 0x60, 0xDB, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};
ISR(TIMER1_COMPA_vect)
{
	static uint8_t x=0;	
	PORTA = segments[x];
	if(x<10)
	{
			x++;
	}
	else{
			x=0;
	}
}


int main(){

	DDRA = 0xFF;
	//DDRB |= _BV(PB7);
	 /* Timer 1 CTC Mode 4 */
	 TCCR1A = 0;
	 TCCR1B = _BV(WGM12);
	 /* Prescaler /1024 */
	 TCCR1B |= _BV(CS12) | _BV(CS10);
	 /* Set timeout at 500ms */ //11719 for 1s
	 OCR1A = 5859;
	 /* Enable interrupt */
	 TIMSK1 |= _BV(OCIE1A);
	 sei();
	 while(1);
		 }
