const int pingPin = 11;
long duration, cm;
long microsecondsToCentimeters(long microseconds)
{return microseconds;
}
void setup() {
Serial.begin(9600);
}

void loop() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  
   duration = pulseIn(pingPin, HIGH); 
   cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  
  delay(100);
}
