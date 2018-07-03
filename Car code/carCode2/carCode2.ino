
int m1f=2;
int m1b=4;
int m1e=5;
int m2f=8;
int m2b=12;
int m2e=6;
/*int sen1=3;
int sen2=7;
int sen3=5;
int LeftSen= 1;
int RightSen=1;
int Center= 1 ; */
void forward(int velocity );
void backward(int velocity);
void right(int velocity);
void left(int velocity);
void stopcar();
//void inc_speed();
//void dec_speed();
void ultrasonic();
void linefollower();

//for ultrasonic
const int trigPin = 11;     // defines pins numbers
const int echoPin = 10;

char re;
long duration, cm;
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2 ;
}

//........................
int velocity;
void setup() {
  pinMode(m1f, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m1e, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m2e, OUTPUT);

  //line follower
  /*pinMode(sen1,INPUT); 
   pinMode(sen2,INPUT);
     pinMode(sen3,INPUT);*/
 
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
    velocity = 254;
  }


 
    }
    if(re=='F'){forward( velocity);}
    if(re=='B'){backward( velocity);}
    if(re=='R'){right( velocity);}
    if(re=='L'){left( velocity); }
    if(re=='S'){stopcar();}
//  if(re=='A'){linefollower();}
    
    
    Serial.println(re);
    ultrasonic();
          
}
/*line folower*/
/* void linefollower(){ 
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
 
} */

  /*****************************/
void ultrasonic(){
  delay(100);
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
    delay(700);
    stopcar();
  }
  
  } 

void forward(int velocity){
    
  analogWrite(5, velocity);
  analogWrite(6, velocity);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  Serial.println(re);
  }
  
void backward(int velocity){
  analogWrite(5, velocity);
  analogWrite(6, velocity);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2b, HIGH);
  
  }

  
void right(int velocity){
  analogWrite(5, velocity);
  analogWrite(6, velocity);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
  
void left(int velocity){
  analogWrite(5, velocity);
  analogWrite(6, velocity);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
  
void stopcar(){
  analogWrite(5, velocity);
  analogWrite(6, velocity);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);  
  }
  
