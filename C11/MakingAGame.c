//avr-gcc -mmcu=atmega644p -DF_CPU=12000000 -Wall -Os -c MakingAGame.c -o MakingAGame.o
//avr-gcc -mmcu=atmega644p -L. -o MakingAGame.elf MakingAGame.o -llcd
//avr-objcopy -O ihex MakingAGame.elf MakingAGame.hex
//avrdude -c usbasp -p m644p -U flash:w:MakingAGame.hex


#define F_CPU 12000000UL  // 12 MHz
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(){
init_lcd();
int x = 117;
int y = 157;
int i = 1;
int j = -1;
int d = 4;
int tempx = x;
int tempy = y;
rectangle ball = {x, x+6, y, y+6};
fill_rectangle(ball,RED);
_delay_ms(d);
fill_rectangle(ball,BLACK);
x=x+i;
y=y+j;

DDRD = 0x00;
PORTD = 0xFF;
int a = 95;
int b = 260;
int score = 0;

while(1){

display.x = 0;
display.y = 0;

display_char('0' + score);
rectangle ball = {x, x+6, y, y+6};
fill_rectangle(ball,RED);
_delay_ms(d);
fill_rectangle(ball,BLACK);

x=x+i;
y=y+j;


if(tempx<x && tempy>y)
{
tempx = x;
tempy = y;


if(x+6==240)
{
i=-1;
j=-1;
}

else if(y-6==0)
{
i=1;
j=1;
}
}

else if(tempx>x && tempy>y)
{
tempx = x;
tempy = y;

if(x-6==0)
{
i=1;
j=-1;

}

else if(y-6==0)
{
i=-1;
j=1;

}

}

else if(tempx<x && tempy<y)
{
tempx = x;
tempy = y;

if(x+6==240)
{
i=-1;
j=1;

}

else if(y+6==320)
{
break;

}
else if(y==b-7){

if(a<=x){

if(x<=a+50){

i=1;
j=-1;

score = score+1;

}
}
}

}

else if(tempx>x && tempy<y)
{
tempx = x;
tempy = y;

if(x-6==0)
{
i=1;
j=1;

}

else if(y+6==320)
{
break;

}

else if(y==b-7){

if(a<=x+6){

if(x+6<=a+50){

i=-1;
j=-1;

score = score+1;

}
}
}

}

else
{
display_string("broken");

}



rectangle bat = {a, a+50, b, b+3};
fill_rectangle(bat,CYAN);


_delay_ms(d);

if(!(PIND & _BV(PD6))){

if(a == 5 ){

a=a+0;
}

else{

fill_rectangle(bat,BLACK);

a=a-1;
}

}

else if(!(PIND & _BV(PD7))){

if(a+50 == 235){

a=a+0;
}

else{

fill_rectangle(bat,BLACK);

a=a+1;

}


}

}

clear_screen();
display.x = 70;
display.y = 160;


display_string("Game Over! Score = ");
display_char('0'+score);


return(0);

}
