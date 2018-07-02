#include <avr/io.h>
#include <util/delay.h>
int sen1=3;
int sen2=7;
int sen3=5;
int LeftSen= 1;
int RightSen=1;
int Center= 1 ;
void forward(int velocity );
void backward(int velocity);
void right(int velocity);
void left(int velocity);
void stopcar();
void inc_speed();
void dec_speed();
void ultrasonic();
void linefollower();

//for ultrasonic
const int trigPin = 11;     // defines pins numbers
const int echoPin = 10;
const int vcc = 7 ;
char re;
long duration, cm;
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2 ;
}

//........................
int velocity;
void setup() {
  DDRB |= 1 << PINB1;  //setting B1 as an output
  DDRD |= 1 << PIND2;  //setting D2 as an output
  DDRD |= 1 << PIND4;  //setting D4 as an output
  DDRD |= 1 << PIND6;  //setting D6 as an output
  DDRB |= 1 << PINB0;  // setting B0 as an output
  DDRB |= 1 << PINB4;  // setting B4 as an output

  //line follower
    pinMode(sen1,INPUT); 
   pinMode(sen2,INPUT);
     pinMode(sen3,INPUT);
   /*..............*/

  //---setting fast pwm mode bits on TC0 Control Register A ---// 
    TCCR0A |=1<<COM0A1 ;
    TCCR0A |=1<<WGM00 ;
    TCCR0A |=1<<WGM01 ;
    //--------------------------------------------//
    
   //---setting fast pwm mode bits on TC0 Control Register B ---//
      TCCR0B |=1<<CS00 ; //no prescalling
    //-----------------------------------------------------------// 

        //---setting fast pwm mode bits on TC1 Control Register A ---// 
    TCCR1A |=1<<COM1A1 ;
    TCCR1A |=1<<WGM10 ;
    TCCR1B |=1<<WGM12 ;
    //--------------------------------------------//


   //---setting fast pwm mode bits on TC1 Control Register B ---//
      TCCR1B |=1<<CS10 ; //no prescalling
    //-----------------------------------------------------------// 
  
  //for Ultrasonic
 pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
 
 Serial.begin(9600);         // Starts the serial communication
}

void loop() {
  if(Serial.available()){
      re=Serial.read();  

  if ( re == '1' ){
    velocity = 0;
  }else if ( re == '2' ){
    velocity = 100;
  }else if (re == '3' ){
    velocity = 200;
  }else if (re == '4' ){
    velocity = 255;
  }


 
    }
    if(re=='F'){forward( velocity);}
    if(re=='B'){backward( velocity);}
    if(re=='R'){right( velocity);delay (500); stopcar();}
    if(re=='L'){left( velocity); delay (500); stopcar(); }
    if(re=='S'){stopcar();}
    if(re=='A'){linefollower();}
    
    Serial.println(re);
   // ultrasonic();
          
}
/*line folower*/
void linefollower(){ 
  RightSen=digitalRead(sen1);
  Center=digitalRead(sen3);
  LeftSen=digitalRead(sen2);
  
  if ((RightSen==HIGH & LeftSen==HIGH)| Center==HIGH)
  {
    forward(velocity);
  }

  else if((RightSen==HIGH & LeftSen==LOW & Center==LOW)|( RightSen==HIGH & LeftSen==LOW & Center==HIGH))
  {
    right(velocity);
  }
  else if((RightSen==LOW & LeftSen==HIGH &  Center==HIGH)|( RightSen==LOW & LeftSen==HIGH & Center==LOW))
  {
    left(velocity);
  }
 
}

  /*****************************/
/*void ultrasonic(){
  digitalWrite(trigPin, LOW);       // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds
 
   cm = microsecondsToCentimeters(duration);
  //Serial.print(cm);
  //Serial.print("cm");
               

     if(cm<30) 
  {
    stopcar();
    delay(1000);
    backward(velocity);
    delay(500);
    left(velocity);   // turn left
    delay(400);
    stopcar();
  }
  
  } */

void forward(int velocity){
  OCR0A = velocity ;
  OCR1A = velocity ;  
  PORTD &= 0 << PIND4 ; //M1B LOW
  PORTB &= 0 << PINB4 ; //M2B LOW
  PORTD |= 1 << PIND2 ; //M1F high 
  PORTB |= 1 << PINB0 ; //M2F high 
  Serial.println(re);
  }
  
void backward(int velocity){
  OCR0A = velocity ;
  OCR1A = velocity ;
  PORTD &= 0 << PIND2 ; //M1F low
  PORTB &= 0 << PINB0 ; //M2F low
  PORTD |= 1 << PIND4 ; //M1B high
  PORTB |= 1 << PINB4 ; //M2B high
  
  }

  
void right(int velocity){
  OCR0A = velocity ;
  OCR1A = velocity ;
  PORTD |= 1 << PIND4 ; //M1B high
  PORTB &= 0 << PINB4 ; //M2B low
  PORTD &= 0 << PIND2 ; //M1F LOW 
  PORTB |= 1 << PINB0 ; //M2F high 
  }
  
void left(int velocity){
  OCR0A = velocity ;
  OCR1A = velocity ;
  PORTD &= 0 << PIND4 ; //M1B low
  PORTB |= 1 << PINB4 ; //M2B high
  PORTD |= 1 << PIND2 ; //M1F high 
  PORTB &= 0 << PINB0 ; //M2F low 
  }
  
void stopcar(){
  OCR0A = velocity ;
  OCR1A = velocity ;
  PORTD &= 0 << PIND4 ; //M1B low
  PORTB &= 0 << PINB4 ; //M2B low
  PORTD &= 0 << PIND2 ; //M1F low 
  PORTB &= 0 << PINB0 ; //M2F low   
  }
  
  
/*void inc_speed(){
  
  OCR0A +=50; 
  OCR0B +=50; 
  
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
  }  */
