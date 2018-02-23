
const int ledpin0 = 0;             
const int ledpin1 = 1;
int BTstate ;
                                                
void setup ( )
{
  pinMode(ledpin0, OUTPUT);
  pinMode(ledpin1, OUTPUT); 
  digitalWrite (ledpin0 ,LOW);
  digitalWrite (ledpin1 ,LOW); 
  Serial.begin(38400) ;                                                      
}

void loop(){
if (Serial.available() > 0){
  BTstate = Serial.read();
  if (BTstate == '0'){
  digitalWrite(ledpin0, HIGH); 
  }
  else{digitalWrite(ledpin0, LOW);}
  if (BTstate == '1'){           
  digitalWrite(ledpin1, HIGH);   
  }
  else{digitalWrite(ledpin1, LOW);}     
}
}

