#include <avr/io.h>
#include <util/delay.h>

void forward(int velocity);
void back(int velocity);
void right(int velocity);
void left(int velocity);
void ultrasonic();

int main (void){
   DDRD = 0b01100000 ; //setting D5 & D6 as an output
   DDRB = 0b00000110 ; // setting B1& B2 as an output
  }
  
void setup() {
}

void loop() {
  
}

void ultrasonic(){
  
  }


void forward(int velocity){
  PORTD = 0b00100000 ; //D5 high (M1F)
  PORTB = 0b00000010 ; //B1 high (M2F)
  }
void back(int velocity){
  PORTD = 0b01000000 ; //D6 high (M1B)
  PORTB = 0b00000100 ; //B2 high (M2B)
  }
void right(int velocity){
  PORTD = 0b00000000 ; //M1 STOPS 
  PORTB = 0b00000010 ; //B1 high (M2F)
  }
void left(int velocity){
  PORTD = 0b00100000 ; //D5 high (M1F)
  PORTB = 0b00000010 ; //M2 STOPS
  }
void stopcar(){
  PORTD = 0b00000000 ; //M1 STOPS
  PORTB = 0b00000010 ; //M2 STOPS
  }  
