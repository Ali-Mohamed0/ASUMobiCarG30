const int ledpin1=4,ledpin2=5,ledpin3=6,ledpin4=7;
void setup() {
pinMode(ledpin1,OUTPUT);
pinMode(ledpin2,OUTPUT);
pinMode(ledpin3,OUTPUT);
pinMode(ledpin4,OUTPUT);
}

void loop() {
digitalWrite(ledpin1,HIGH);
  digitalWrite(ledpin2,LOW);
  digitalWrite(ledpin3,LOW);
  digitalWrite(ledpin4,LOW);
  delay(1000);
  digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,HIGH);
  digitalWrite(ledpin3,LOW);
  digitalWrite(ledpin4,LOW);
  delay(1000);
  digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,LOW);
  digitalWrite(ledpin3,HIGH);
  digitalWrite(ledpin4,LOW);
  delay(1000);
  digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,LOW);
  digitalWrite(ledpin3,LOW);
  digitalWrite(ledpin4,HIGH);
  delay(1000);
  digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,LOW);
  digitalWrite(ledpin3,HIGH);
  digitalWrite(ledpin4,LOW);
  delay(1000);
  digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,HIGH);
  digitalWrite(ledpin3,LOW);
  digitalWrite(ledpin4,LOW);
  delay(1000);
  
}
