
//========== SEED Electronics/Coding Workshop Exercise 11b ==========

//Purpose: Light meter as graphical bar graph
//Date: May 28, 2018


#include "BBGame115.h"
Display display;


//--- Constant definitions ---
#define PHOTORESISTOR   A0


void setup() 
{
  //Initialize LED matrix display
  display.Setup(11,5);

  //Input for photoresistor
  pinMode(PHOTORESISTOR,INPUT);
  
  //Serial communication with computer over USB
  Serial.begin(115200);
  Serial.println("Hello");
}


//--- Global variables ---
int light = 0;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Read analog input A0 from photoresistor
  light = analogRead(PHOTORESISTOR);

  //Calculate a value based on light reading from photoresistor
  int X = map(light,270,670,0,10);
  if (X < 0) X = 0;
  if (X > 10) X = 10;

  //Send light, X variable values to print on Serial Monitor
  Serial.print(light);
  Serial.print(" --- ");
  Serial.println(X);  

  //Draw a vertical bar of height X and scroll display
  display.Clear();
  display.hLine(1,0,X);
  display.hLine(2,0,X);
  delay(100);
}

