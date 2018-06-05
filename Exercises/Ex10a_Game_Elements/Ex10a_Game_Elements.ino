
//========== SEED Electronics/Coding Workshop Exercise 10a ==========

//Purpose: Game spaceship element that moves with buttons
//Date: June 2, 2018  


#include "BBGame114.h"
Display display;
Buttons buttons;


//---------- Setup routine to run once ----------

void setup()
{
  display.Setup(11, 4);
  buttons.Setup();
}


//--- Global variables ---

int counter = 0;
int d = 20;

int shipPos = 0;


//---------- Loop routine that runs repeatedly ----------

void loop()
{
  display.Clear();
  DrawSpaceship();

  if(buttons.BtnPressed(BTN2)) MoveSpaceship(+1);
  if(buttons.BtnPressed(BTN3)) MoveSpaceship(-1);

  counter++;
  delay(d);
}

void DrawSpaceship()
{
  display.SetPixel(0,shipPos);
  display.SetPixel(1,shipPos);
}

void MoveSpaceship(int dir)
{
  if (dir == +1) shipPos++;
  if (dir == -1) shipPos--;

  if (shipPos < 0) shipPos = 0;
  if (shipPos > 3) shipPos = 3;
}

