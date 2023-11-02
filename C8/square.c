/*  Author: Klaus-Peter Zauner
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 */
  //FOR OCR1A USE D5
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 12000000 //12MHz

#define FREQ 262 //was inititally 4000


unsigned long toneClock;   /* set at timer initialisation and used
                              to calculate TOP when setting frequency */ 

void init_tone(void);
void tone(uint16_t frequency);

int main(void) {

    init_tone();
    
    for (;;) tone(FREQ);

}


/* init_tone ---
   Setup timer as a tone frequency oscillator.
*/
void init_tone(void)
{
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

