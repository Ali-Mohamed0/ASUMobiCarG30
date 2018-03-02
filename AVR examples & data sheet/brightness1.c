#include <avr/io.h>
#include <util/delay.h>

//initialize pwm

void pwm_tim0 ()
{

//intialize timer0 in pwm mode

TCCRO |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
//OC0 is an output pin,  WGM and COM won’t  come into play unless..
DDRB |= (1<<PB3) ;


}

 void main ()
 {
  uint8_t brightness; 
  //initialize timer0 in pwm mode 
  
    pwm_tim0 () ;
	
	while(1)
	{
	
	//increasing 
	     for (brightness = 0; brightness < 255; ++brightness)
		 {
		    OCR0 = brightness; //set the brightness as duty cycle 
			 _delay_ms(10);    //to see the change 
		 }
	     
	//decreasing 
		 for (brightness = 255; brightness > 0; --brightness)
		 {
		    OCR0 = brightness; 
		    _delay_ms(10);
		}
			
	
	
	}
 
 
 
 
 }