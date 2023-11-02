/* embedded_boost.c 
 *
 *  Author: Steve Gunn & Klaus-Peter Zauner 
 * Licence: This work is licensed under the Creative Commons Attribution License. 
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: 
 *          - Use with a terminal program
 * 
 *          - F_CPU must be defined to match the clock frequency
 *
 *          - Compile with the options to enable floating point
 *            numbers in printf(): 
 *               -Wl,-u,vfprintf -lprintf_flt -lm
 *
 *          - Pin assignment: 
 *            | Port | Pin | Use                         |
 *            |------+-----+-----------------------------|
 *            | A    | PA0 | Voltage at load             |
 *            | D    | PD0 | Host connection TX (orange) |
 *            | D    | PD1 | Host connection RX (yellow) |
 *            | D    | PD7 | PWM out to drive MOSFET     |
 *avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -Wl,-u,vfprintf -lprintf_flt -lm  embedded_boost_.c -o embedded_boost_.elf  -Wl,-u,vfprintf -lprintf_flt -lm
 *avr-objcopy -O ihex embedded_boost_.elf embedded_boost_.hex
 *avrdude -c usbasp -p m644p -U flash:w:embedded_boost_.hex
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define DELAY_MS      500
#define BDRATE_BAUD  9600

#define ADCREF_V     3.3
#define ADCMAXREAD   1023   /* 10 bit ADC */

/* Find out what value gives the maximum
   output voltage for your circuit:
*/
#define PWM_DUTY_MAX 240    /* 94% duty cycle */
		
void init_stdio2uart0(void);
int uputchar0(char c, FILE *stream);
int ugetchar0(FILE *stream);
double v_target=5;
int duty=0;
		
void init_adc(void);
double v_load(void);

void init_pwm(void);
void pwm_duty(uint8_t x);
void set_pwm(float v_input);


int main(void)
{
	uint16_t cnt =0;
        	
	init_stdio2uart0();
	init_pwm(); 
	init_adc();
	

	for(;;) {	    
	    printf( "%04d:  ", cnt );

	//    pwm_duty(255);   /* Limited by PWM_DUTY_MAX */
	
	set_pwm(6.0);
	    	
	    printf( "  -->  %5.3f V\r\n", v_load() );
	    _delay_ms(DELAY_MS);
	    cnt++;
	}
}

int uputchar0(char c, FILE *stream)
{
	if (c == '\n') uputchar0('\r', stream);
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = c;
	return c;
}

int ugetchar0(FILE *stream)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void init_stdio2uart0(void)
{
	/* Configure UART0 baud rate, one start bit, 8-bit, no parity and one stop bit */
	UBRR0H = (F_CPU/(BDRATE_BAUD*16L)-1) >> 8;
	UBRR0L = (F_CPU/(BDRATE_BAUD*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

	/* Setup new streams for input and output */
	static FILE uout = FDEV_SETUP_STREAM(uputchar0, NULL, _FDEV_SETUP_WRITE);
	static FILE uin = FDEV_SETUP_STREAM(NULL, ugetchar0, _FDEV_SETUP_READ);

	/* Redirect all standard streams to UART0 */
	stdout = &uout;
	stderr = &uout;
	stdin = &uin;
}


void init_adc (void)
{
    /* REFSx = 0 : Select AREF as reference
     * ADLAR = 0 : Right shift result
     *  MUXx = 0 : Default to channel 0
     */
    ADMUX = 0x00;
    /*  ADEN = 1 : Enable the ADC
     * ADPS2 = 1 : Configure ADC prescaler
     * ADPS1 = 1 : F_ADC = F_CPU / 64
     * ADPS0 = 0 :       = 187.5 kHz
     */
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);
}


double v_load(void)
{
     uint16_t adcread;
         
     /* Start single conversion */
     ADCSRA |= _BV ( ADSC );
     /* Wait for conversion to complete */
     while ( ADCSRA & _BV ( ADSC ) );
     adcread = ADC;
    
     printf("ADC=%4d", adcread);  
 
     return (double) (adcread * ADCREF_V/ADCMAXREAD);
}



void init_pwm(void)
{
    /* TIMER 2 */
    DDRD |= _BV(PD6); /* PWM out */
    DDRD |= _BV(PD7); /* inv. PWM out */
    

    TCCR2A = _BV(WGM20) | /* fast PWM/MAX */
	     _BV(WGM21) | /* fast PWM/MAX */
	     _BV(COM2A1); /* A output */
    TCCR2B = _BV(CS20);   /* no prescaling */   
}


/* Adjust PWM duty cycle
   Keep in mind this is not monotonic
   a 100% duty cycle has no switching
   and consequently will not boost.  
*/
void pwm_duty(uint8_t x) 
{
    x = x > PWM_DUTY_MAX ? PWM_DUTY_MAX : x;
    
    printf("PWM=%3u  ==>  ", x);  

    OCR2A = x;
}
/*
void set_pwm(float v_input)
{
	double v_out = (v_load()*5.53);
	if(((v_target * 1.01) > v_out)&&(v_out > (v_target * 0.99))){
		duty = duty;
	}
	else if ((v_target * 0.99) > v_out){
		duty = duty + 1;
	}
	else if ( v_out > (v_target * 1.01)){
		duty = duty -1;
	}
	pwm_duty(duty);
}

*/

void set_pwm(float v_input)
{
	float v_out = (v_load()*5.53);
	if(((v_input * 1.01) > v_out)&&(v_out > (v_input * 0.99))){
		duty = duty;
	}
	else if ((v_input * 0.99) > v_out){
		duty = duty + 5;
	}
	else if ( v_out > (v_input * 1.01)){
		duty = duty -5;
	}
	pwm_duty(duty);
}


