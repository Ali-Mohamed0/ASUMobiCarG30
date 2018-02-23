#include <avr/io.h>
#include <avr/delay.h> 
int main(void) { 
  DDRB |= 1 << PINB0;  
while(1){
  PORTB ^= 1 << PINB0; 
  _delay_ms(1000);      
  }
 }
