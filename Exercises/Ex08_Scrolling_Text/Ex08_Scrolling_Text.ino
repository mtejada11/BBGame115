
//========== SEED Electronics/Coding Workshop Exercise 8 ==========

//Purpose: Scrolling text on 11x4 LED matrix
//Date: May 24, 2018


#include "BBGame114.h"
Display display;
TextDisplay textDisplay(display);


//---------- Setup routine to run once ----------

void setup() 
{
  //Initialize LED matrix display
  display.Setup(11,4);
}


//--- Global variable ---
int counter = 0;
String text = "ABCDE 12345";


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Draw text using scrolling text function and counter for position
  textDisplay.ScrollText(text, counter);
  counter++;
  delay(100);
}




