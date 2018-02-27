#include <avr/io.h>
#include <avr/delay.h> 
#include <avr/interrupt.h>

float dutycycle = 0 ;

int main (void){
  
   DDRD |= 1 << PIND6 ; //setting pin d6 as an output

    //---setting fast pwm mode bits on TC0 Control Register A ---// 
    TCCR0A |=1<<COM0A1 ;
    TCCR0A |=1<<WGM00 ;
    TCCR0A |=1<<WGM01 ;
    OCR0A = (dutycycle/100)*255 ; //gets the fraction that represent the amout of time the signal will be high 
    //--------------------------------------------//


   //---setting fast pwm mode bits on TC0 Control Register B ---//
      TCCR0B |=1<<CS00 ; //no prescalling
    //-----------------------------------------------------------// 


   //--setting interrupts--//
    sei();
    TIMSK0 |= 1 << TOIE0 ; //enable overflow interrupt
    // ----------------------// 

   

 while(1){
    // PORTD |=1<<PIND6 ; // SETTING D6 HIGH
    _delay_ms(100);
    dutycycle +=10;

    if (dutycycle> 100){
      dutycycle = 0 ; //resetting dutycycle if it exceeds 100
      }
  }

}

ISR(TIMER0_OVF_VECT){
  OCR0A = (dutycycle/100)*255 ; 
  //law 7asal overflow it gets here and recalculate the dutycycle
  }




