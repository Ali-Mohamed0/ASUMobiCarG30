
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
void forwardright(int velocity );
void forwardleft(int velocity );
void backward(int velocity);
void right(int velocity);
void left(int velocity);
void stopcar();
void ultrasonic();
void linefollower();
int readLongNum();
void displacement(int dist);
void angle(int ang);
void rect();
void circ();
void inf();
void drawShapes();

//for ultrasonic
const int trigPin = 11;     // defines pins numbers
const int echoPin = 10;
char ultra='u';

int delPercm=60;
int delPerang=10;
int speedratio=2;
int circuleDelay=2500;

char re;
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
  delay(50);
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
    if(re=='A'){linefollower();}
    if(re=='U'){ultra='U';}
    if(re=='u'){ultra='u';}
    if(re=='D'){displacement(readLongNum());re='e';}
    if(re=='G'){angle(readLongNum());re='e';}
    if(re=='T'){velocity=readLongNum();re='e';}
    if(re=='d'){delPercm=readLongNum();re='e';}
    if(re=='a'){delPerang=readLongNum();re='e';}
    if(re=='r'){speedratio=readLongNum();re='e';}
    if(re=='c'){circuleDelay=readLongNum();re='e';}
    if(re=='h'){drawShapes();re='e';}
    
    Serial.println(re);
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
    
  analogWrite(m1e, velocity);
  analogWrite(m2e, velocity);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
  void forwardright(int velocity ){
  analogWrite(m1e, velocity/speedratio);
  analogWrite(m2e, velocity);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
void forwardleft(int velocity ){
   analogWrite(m1e, velocity);
  analogWrite(m2e, velocity/speedratio);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
}
void backward(int velocity){
  analogWrite(m1e, velocity);
  analogWrite(m2e, velocity);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2b, HIGH);
  
  }

  
void right(int velocity){
  analogWrite(m1e, velocity);
  analogWrite(m2e, velocity);
  digitalWrite(m1f, LOW);
  digitalWrite(m2f, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
  
void left(int velocity){
  analogWrite(m1e, velocity);
  analogWrite(m2e, velocity);
  digitalWrite(m1f, HIGH);
  digitalWrite(m2f, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2b, LOW);
  }
  
void stopcar(){
  analogWrite(m1e, velocity);
  analogWrite(m2e, velocity);
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
void displacement(int dist){
  forward( velocity);
  delay(dist*delPercm);
  stopcar();
}
void angle(int ang){
  left(velocity);
  delay(ang*delPerang);
  stopcar();
}
void rect(){
  displacement(170);
  angle(90);
  displacement(170);
  angle(90);
  displacement(170);
  angle(90);
  displacement(170);
  angle(90);
}
void circ(){
  forwardleft(velocity);
  delay(circuleDelay);
  stopcar();
}
void inf(){
   forwardleft(velocity);
  delay(circuleDelay);
  forwardright(velocity);
  delay(circuleDelay);
  stopcar();
}
void drawShapes(){
  rect();
  delay(10000);
  circ();
  delay(10000);
  inf();
}

