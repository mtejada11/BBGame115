
//========== SEED Electronics/Coding Workshop Exercise 7 ==========

//Purpose: Rotating pattern created by setting individual pixels
//Date: May 28, 2018


#include "BBGame115.h"
Display display;


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
  display.Clear();

  //Draw one pixel in the center
  display.SetPixel(2,1);

  //Based on the counter value, draw pixels to create rotating pattern
  if (counter == 0) { display.SetPixel(2,0); }
  if (counter == 1) { display.SetPixel(1,0); }
  if (counter == 2) { display.SetPixel(1,1); display.SetPixel(0,1); }
  if (counter == 3) { display.SetPixel(1,2); display.SetPixel(0,3); }
  if (counter == 4) { display.SetPixel(2,2); display.SetPixel(2,3); }
  if (counter == 5) { display.SetPixel(3,2); display.SetPixel(4,3); }
  if (counter == 6) { display.SetPixel(3,1); display.SetPixel(4,1); }
  if (counter == 7) { display.SetPixel(3,0); }
  delay(100);

  //Increment counter
  counter++;
  if (counter > 7) counter = 0;
}

