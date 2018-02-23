#define ledPin 13
int i=255;

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(ledPin,i);
delay(500);
i=i-55;
if(i<0)
i=255;
}
