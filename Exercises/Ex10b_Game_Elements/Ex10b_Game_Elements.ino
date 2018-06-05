
//========== SEED Electronics/Coding Workshop Exercise 10b ==========

//Purpose: Game spaceship and firing laser elements
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
int laserPos = 0;
int laserDistance = 0;
bool laserFired = false;


//---------- Loop routine that runs repeatedly ----------

void loop()
{
  display.Clear();
  DrawSpaceship();
  DrawLaser();
  UpdateLaser();

  if(buttons.BtnPressed(BTN1)) FireLaser(shipPos); 
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


void FireLaser(int pos)
{
  laserFired = true;
  laserPos = pos;
  laserDistance = 0;
}


void DrawLaser()
{
  if (laserFired == true)
    display.SetPixel(laserDistance,laserPos);
}


void UpdateLaser()
{
  if (laserFired == true) laserDistance++;
  if (laserDistance > 10) laserFired = false;
}
