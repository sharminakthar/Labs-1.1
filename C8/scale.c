/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */

#include <avr/io.h>
#include <util/delay.h>
#include "et_scale.h"

#define FREQ 4000

unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */ 

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {
	
	int i;
    init_tone();
    
	for(;;){
		for (i=0; i< ET_SCALE_TOP; i++){
			tone(et_scale[i]);
			_delay_ms(100);
		}
		for (i=ET_SCALE_TOP; i>=0; i--){
			tone(et_scale[i]);
			_delay_ms(100);
		}
	}
}



/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
// DDRD |= _BV(PD5);
// TCCR1A= _BV(0x41);
// TCCR1B= _BV(0x12);
	
	DDRD |= _BV(PD5); /*enable output driver for OCR1A*/
	TCCR1A = _BV(COM1A0) /*toggle OC1A on match*/
	| _BV(WGM10); /*frequency (f) correct PWM */
	TCCR1B = _BV(WGM13) /*varying f with OCR1A*/
	| _BV(CS11); /*prescaler set to 8*/
}

/* tone ---
   Set oscillator output to desired frequency
*/
void tone(uint16_t frequency)
{
	OCR1A = (uint16_t) (F_CPU/ (2*2*8)/frequency); 
}

