
int m1f=2;
int m1b=4;
int m1e=5;
int m2f=8;
int m2b=12;
int m2e=6;

int r=0;
int l=0;
int c=1;
int sen3=5;
//line follower
int LeftSen= 3;
int RightSen=13;
int CenterSen= 9 ; 
void forward(int velocity );
void backward(int velocity);
void right(int velocity);
void left(int velocity);
int readLongNum();
void stopcar();
//void inc_speed();
//void dec_speed();
void ultrasonic();
void linefollower();

//for ultrasonic
const int trigPin = 11;     // defines pins numbers
const int echoPin = 10;
char ultra='u';

char re;
char temp_re;
long duration, cm;
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2 ;
}

//........................
int velocity;
void setup() {
  delay(10);
  pinMode(m1f, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m1e, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m2e, OUTPUT);

  //line follower
  pinMode(LeftSen,INPUT); 
  pinMode(RightSen,INPUT);
  pinMode(CenterSen,INPUT);
 
  //for Ultrasonic
 pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
 
 Serial.begin(9600);         // Starts the serial communication
}

void loop() {
  temp_re=Serial.read();  
  if(temp_re=='1'|temp_re=='2'|temp_re=='3'|temp_re=='4'|temp_re=='F'|temp_re=='L'|temp_re=='R'|temp_re=='S'
  |temp_re=='B'|temp_re=='A'|temp_re=='U'|temp_re=='u'|temp_re=='t'){
    re=temp_re;
  }
    

  if ( re == '1' ){
    velocity = 0;
  }else if ( re == '2' ){
    velocity = 100;
  }else if (re == '3' ){
    velocity = 200;
  }else if (re == '4' ){
    velocity = 254;
  }


 
    
    if(re=='F'){forward( velocity);}
    if(re=='B'){backward( velocity);}
    if(re=='R'){right( velocity);}
    if(re=='L'){left( velocity); }
    if(re=='S'){stopcar();}
    if(re=='A'){linefollower();}
    if(re=='U'){ultra='U';}
    if(re=='u'){ultra='u';}
    if(re=='t'){
      Serial.println(readLongNum());re='e';}
    //Serial.println(re);
    if(ultra=='U'){
      ultrasonic();
    }
    
          
}
/*line folower*/
 void linefollower(){ 
  r=digitalRead(RightSen);
  c=digitalRead(CenterSen);
  l=digitalRead(LeftSen);
  
  if (!l & c & !r)
  {
    forward(velocity);
  }

  else if(!l & !c & r )
  {
    right(velocity);
  }
  else if(l & !c & !r)
  {
    left(velocity);
  }
 
} 

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

int readLongNum(){
  int NumLen;
  int tempNum;
  int rightNum=0;
  int i;
  int sflag=1;
 
  while(1){
    if(Serial.available()){
      if(sflag==1){
        NumLen=Serial.read();
        i=NumLen-'0';
        sflag=0;
      }else{
        tempNum=Serial.read();
        i--;
      
        if(tempNum=='q')break;
        else {
          tempNum=tempNum - '0';
          rightNum+=tempNum*pow(10,i);
        }
      }
    }
  }

return rightNum;
  
}


