
void setup()  
{ 
  //Set up pin to use
  pinMode(2,OUTPUT);
}

void loop()  
{
  //Turn LED on
  digitalWrite(2,HIGH);
  delay(200);

  //Turn LED off
  digitalWrite(2,LOW);
  delay(200);
}

