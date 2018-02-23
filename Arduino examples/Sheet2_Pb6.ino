int sensorPin1 = A0;// select the input pin for the analog input (sensor)
int sensorPin2 = A1;
int sensorPin3 = A2;

int ledPin1 = 13;      // select the pin for the LED
int ledPin2 = 12;
int ledPin3 = 11;

int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;
int sensorValue3 = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);      // declare the ledPin as an OUTPUT:
  pinMode(ledPin2, OUTPUT);   
  pinMode(ledPin3, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
   sensorValue1 = analogRead(sensorPin1);
   sensorValue2 = analogRead(sensorPin2);
   sensorValue3 = analogRead(sensorPin3);

if( (sensorValue1 >= sensorValue2) && (sensorValue1 >= sensorValue3) )
 {
   digitalWrite(ledPin1, HIGH);     // turn the ledPin1 on
   delay(1000);
 }
 else if ( (sensorValue2 >= sensorValue1) && (sensorValue2 >= sensorValue3) )
 {
   digitalWrite(ledPin2, HIGH);     // turn the ledPin2 on
   delay(1000);
 }

else 
  {
   digitalWrite(ledPin3, HIGH);     // turn the ledPin3 on
   delay(1000);
  }
 
}
