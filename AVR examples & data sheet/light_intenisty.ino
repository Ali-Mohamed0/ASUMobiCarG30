#include <avr/io.h>
#include <avr/delay.h> 
#include <avr/interrupt.h>

int x = 0 ;

int main (void){
  
   DDRD |= 1 << PIND6 ; //setting pin d6 as an output

    //---setting fast pwm mode bits on TC0 Control Register A ---// 
    TCCR0A |=1<<COM0A1 ;
    TCCR0A |=1<<WGM00 ;
    TCCR0A |=1<<WGM01 ;
    //--------------------------------------------//


   //---setting fast pwm mode bits on TC0 Control Register B ---//
      TCCR0B |=1<<CS00 ; //no prescalling
    //-----------------------------------------------------------// 


   
   

 while(1){
    // PORTD |=1<<PIND6 ; // SETTING D6 HIGH
   OCR0A =x;
    _delay_ms(100);
    x +=30;

    if (x> 255){
      x = 0 ; //resetting dutycycle if it exceeds 100
      }
  }

}





