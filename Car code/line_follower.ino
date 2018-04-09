
int sen1=4;
int sen2=6;
int Left= HIGH;
int Right=HIGH;


void setup() {
  // put your setup code here, to run once:
   pinMode(sen1,INPUT); 
   pinMode(sen2,INPUT);
   

}
void loop() {
  // put your main code here, to run repeatedly:
  Right=digitalRead(sen1);

  Left=digitalRead(sen2);
  
  if (Right==HIGH & Left==HIGH)
  {
    //forward();
  }

  else if(Right==LOW & Left==HIGH)
  {
    //right();
  }
  else if(Right==HIGH & Left==LOW)
  {
    //left();
  }
  else
  {
    //stopcar();
  }
  
}


