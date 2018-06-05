
//========== SEED Electronics/Coding Workshop Exercise 11a ==========

//Purpose: Using photoresistor input to control LEDs
//Date: June 3, 2018


//--- Constant definitions ---
#define LED1            2
#define LED2            3
#define LED3            4
#define LED4            5
#define LED5            6
#define PHOTORESISTOR   A0


//---------- Setup routine to run once ----------

void setup() 
{

  //Set up pins to use
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(PHOTORESISTOR,INPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
  
  //Serial communication with computer over USB
  Serial.begin(115200);
  Serial.println("Hello");
}


//----- Global variable -----
int light = 0;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Read analog input A0 from photoresistor
  light = analogRead(PHOTORESISTOR);

  //Calculate a value based on light reading from photoresistor
  int X = map(light,200,800,5,0);
  if (X < 0) X = 0;
  if (X > 5) X = 5;
  
  //Send light, x variable values to print on Serial Monitor
  Serial.print(light);
  Serial.print(" --- ");
  Serial.println(X);
  
  LEDControl(X);
  
  delay(100);
}


//Function to control number of LEDs lit based on input
void LEDControl(int X)
{
  switch(X)
  {
    case 0:
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      break;
    case 1:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
    break;
    case 2:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      break;
    case 3:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      break;
    case 4:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,LOW);
      break;
    case 5:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,HIGH);
      break;
    default:
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
  }
}

