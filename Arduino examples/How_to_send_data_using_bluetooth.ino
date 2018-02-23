 
void setup() {
  // put your setup code here, to run once:
   pinMode(12,OUTPUT);
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(Serial.available()){
    char x=Serial.read();
    if(x=='F'){
       digitalWrite(12,HIGH);
    }else if(x=='B'){
      digitalWrite(12,LOW);
    }
    
    Serial.println(x);
    
  }
}
