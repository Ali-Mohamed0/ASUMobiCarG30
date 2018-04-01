#include <avr/io.h>
#include <util/delay.h>

void forward(int velocity );
void backward(int velocity);
void right(int velocity);
void left(int velocity);
void stopcar();
void inc_speed();
void dec_speed();
void ultrasonic();

//for ultrasonic
const int trigPin = 9;     // defines pins numbers
const int echoPin = 10;
char re;

long duration;             // defines variables
int distance;
//........................
int velocity;
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
/* pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
 */
 Serial.begin(9600);         // Starts the serial communication


}

void loop() {
   // digitalWrite(6 , HIGH);
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
    if(re=='R'){right( velocity);}
    if(re=='L'){left( velocity);}
    if(re=='S'){stopcar();}
    Serial.println(velocity);
    
    

  
    
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
    backward(150);
    delay(1000);
    left(150);                               // turn left
    if(distance<30)
      {
        stopcar();
        delay(500);
        backward(150);
        delay(1000);
        left(150);                         
      }  
  }
  
  }

void forward(int velocity){
 OCR0A = velocity ;
 OCR0B = velocity ;  
 OCR1A = velocity ;
 OCR1B = velocity ;
 PORTD &= 0 << PIND6 ; //M1B STOPS
  PORTB &= 0 << PINB2 ; //M2B STOPS
  PORTD |= 1 << PIND5 ; //D5 high (M1F)
  PORTB |= 1 << PINB1 ; //B1 high (M2F) 
  }
  
void backward(int velocity){
  OCR0A = velocity ;
 OCR0B = velocity ;  
 OCR1A = velocity ;
 OCR1B = velocity ;
   PORTD &= 0 << PIND5 ; //M1F STOPS
   PORTB &= 0 << PINB1 ; //M2F STOPS 
// PORTD |= 1 << PIND6 ; //D6 high (M1B)
 digitalWrite(6 , HIGH);
  PORTB |= 1 << PINB2 ; //B2 high (M2B) 
  }

  
void right(int velocity){
  OCR0A = velocity ;
 OCR0B = velocity ;  
 OCR1A = velocity ;
 OCR1B = velocity ; 
 PORTB &= 0 << PINB2 ; //M2B STOPS
  PORTD &= 0 << PIND5 ; //M1F STOPS 
  PORTD &= 0 << PIND6 ; //M1B STOPS  
  PORTB |= 1 << PINB1 ; //B1 high (M2F)
  }
  
void left(int velocity){
  OCR0A = velocity ;
 OCR0B = velocity ;  
 OCR1A = velocity ;
 OCR1B = velocity ;
  PORTB &= 0 << PINB1 ; //M2F STOPS
  PORTB &= 0 << PINB2 ; //M2B STOPS
  PORTD |= 1 << PIND5 ; //D5 high (M1F)
  }
  
void stopcar(){
  OCR0A = velocity ;
 OCR0B = velocity ;  
 OCR1A = velocity ;
 OCR1B = velocity ;
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
