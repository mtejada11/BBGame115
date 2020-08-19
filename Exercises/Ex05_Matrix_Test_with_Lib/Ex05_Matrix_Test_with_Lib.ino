
//========== SEED Electronics/Coding Workshop Exercise 5 ==========

//Purpose: Test 5x4 LED matrix (with library)
//Date: May 22, 2018


#include "BBGame115.h"
Display display;


//---------- Setup routine to run once ----------

void setup() 
{
  //Initialize LED matrix display
  display.Setup(6,4);
}


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
   int d = 150; //ms

 //Flash sequence of horizontal lines
  for(int y = 0; y < 4; y++)
  {
    display.Clear();
    display.hLine(y);
    delay(d);
  }

  //Flash sequence of vertical lines
  for(int x = 0; x < 5; x++)
  {
    display.Clear();
    display.vLine(x);
    delay(d);
  }
}

