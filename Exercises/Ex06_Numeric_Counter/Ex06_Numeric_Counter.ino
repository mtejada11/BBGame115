
//========== SEED Electronics/Coding Workshop Exercise 6 ==========

//Purpose: Numeric counter on 5x4 LED matrix
//Date: May 24, 2018


#include "BBGame114.h"
Display display;
TextDisplay textDisplay(display);


//---------- Setup routine to run once ----------

void setup() 
{
  //Initialize LED matrix display
  display.Setup(5,4);
}


//--- Global variable ---
int counter = 0;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Create text string from counter value
  String text(counter);

  //Draw text string to display
  display.Clear();
  textDisplay.DisplayTextCentered(text);
  delay(500);

  //Increment counter
  counter++;
  if (counter > 9) counter = 0;
}

