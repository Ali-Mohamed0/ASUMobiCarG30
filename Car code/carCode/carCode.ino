#include <avr/io.h>
#include <util/delay.h>

void forward(int velocity);
void back(int velocity);
void right(int velocity);
void left(int velocity);
void stopcar();
void inc_speed();
void dec_speed();
void ultrasonic();

//for ultrasonic
const int trigPin = 9;     // defines pins numbers
const int echoPin = 10;

long duration;             // defines variables
int distance;
//........................

void setup() {
  DDRD |= 1 << PIND5;  //setting D5 as an output
  DDRD |= 1 << PIND6;  //setting D6 as an output
  DDRB |= 1 << PINB1;  // setting B1 as an output
  DDRB |= 1 << PINB2;  // setting B2 as an output

  //---setting fast pwm mode bits on TC0 Control Register A ---// 
    TCCR0A |=1<<COM0A1 ;
    TCCR0A |=1<<WGM00 ;
    TCCR0A |=1<<WGM01 ;
    //--------------------------------------------//
    
   //---setting fast pwm mode bits on TC0 Control Register B ---//
      TCCR0B |=1<<CS00 ; //no prescalling
    //-----------------------------------------------------------// 

        //---setting fast pwm mode bits on TC1 Control Register A ---// 
    TCCR0A |=1<<COM1A1 ;
    TCCR0A |=1<<WGM10 ;
    TCCR0A |=1<<WGM12 ;
    //--------------------------------------------//


   //---setting fast pwm mode bits on TC1 Control Register B ---//
      TCCR0B |=1<<CS10 ; //no prescalling
    //-----------------------------------------------------------// 
  
  //for Ultrasonic
 pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
 Serial.begin(9600);         // Starts the serial communication


}

void loop() {
  
}

void ultrasonic(){
  digitalWrite(trigPin, LOW);       // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds

  distance= duration*0.034/2;             // Calculating the distance

  Serial.print("Distance: ");              // Prints the distance on the Serial Monitor
  Serial.println(distance);

  if(distance<30) 
  {
    stopcar();
    delay(500);
    back(20);
    delay(1000);
    left(10);                               // turn left
    if(distance<30)
      {
        stopcar();
        back(10);
        left(10);                         
      }  
  }
  
  }

void forward(int velocity){
  OCR0A = velocity ;
  OCR1A = velocity ;  //law el velocity hategy mn el app 
  PORTD |= 1 << PIND5 ; //D5 high (M1F)
  PORTB |= 1 << PINB1 ; //B1 high (M2F)
  }
  
void back(int velocity){
  OCR0A = velocity ;
  PORTD |= 1 << PIND6 ; //D6 high (M1B)
  PORTB |= 1 << PINB2 ; //B2 high (M2B)
  }
  
void right(int velocity){
  OCR0A = velocity ;
  OCR0B = velocity ; 
  PORTD &= 0 << PIND5 ; //M1F STOPS 
  PORTD &= 0 << PIND6 ; //M1B STOPS 
  PORTB |= 1 << PINB1 ; //B1 high (M2F)
  }
  
void left(int velocity){
  OCR0B = velocity ;
  PORTD |= 1 << PIND5 ; //D5 high (M1F)
  PORTB &= 0 << PINB1 ; //M2F STOPS 
  PORTB &= 0 << PINB2 ; //M2B STOPS 
  }
  
void stopcar(){
  PORTD &= 0 << PIND5 ; //M1F STOPS 
  PORTD &= 0 << PIND6 ; //M1B STOPS
  PORTB &= 0 << PINB1 ; //M2F STOPS 
  PORTB &= 0 << PINB2 ; //M2B STOPS 
  }

  //law el speed control hatkon mn 2 buttons inc & dec only 
void inc_speed(){
  
  OCR0A +=50; 
  OCR1A +=50;
  OCR0B +=50; 
  OCR1B +=50;  
  
  if (OCR0A > 255){
      OCR0A = 255 ; 
      }
  }
  
void dec_speed(){
  OCR0A -=50; 
  OCR1A -=50;
  OCR0B -=50; 
  OCR1B -=50;
  
   if (OCR0A < 0 ){
     OCR0A = 0 ; 
      }
  }  
