const int trigPin = 11;
const int echoPin = 10;

long duration, cm;
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2 ;
}
void setup() {
Serial.begin(9600);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
}

void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
   duration = pulseIn(echoPin, HIGH); 
   cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  
  delay(100);
}
