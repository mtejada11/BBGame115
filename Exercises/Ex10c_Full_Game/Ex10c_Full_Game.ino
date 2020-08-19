
//========== SEED Electronics/Coding Workshop Exercise 10b ==========

//Purpose: Full game with spaceship, laser and rest of game from library
//Date: June 2, 2018


#include "BBGame115.h"
Display display;
Buttons buttons;

#include "BBGame115SpaceInv.h"
Spaceship ship;
Laser laser;
Aliens aliens;


//---------- Setup routine to run once ----------

void setup()
{
  display.Setup(11, 5);
  buttons.Setup();
}


//--- Global variables ---

int counter = 0;
int d = 20;

int shipPos = 0;
int laserPos = 0;
int laserDistance = 0;
bool laserFired = false;

int numShips = 5;


//---------- Loop routine that runs repeatedly ----------

void loop()
{
  display.Clear();
  DrawSpaceship();
  DrawLaser();
  aliens.Draw(display);

  UpdateLaser();
  laser.CheckHit(aliens);
  laserFired = laser.IsStillFired();
  ship.CheckHit(aliens);
  aliens.Update(counter);

  if ((counter % aliens.NextAlienInterval()) == 0)
    aliens.AddAlien(counter);

  if (buttons.BtnPressed(BTN1)) FireLaser(shipPos);
  if (buttons.BtnPressed(BTN2)) MoveSpaceship(+1);
  if (buttons.BtnPressed(BTN3)) MoveSpaceship(-1);

  counter++;
  delay(d);
}


void DrawSpaceship()
{
  display.SetPixel(0,shipPos);
  display.SetPixel(1,shipPos);
  ship.SetPos(shipPos);
}

void MoveSpaceship(int dir)
{
  if ((dir > 0) && (shipPos < 3)) shipPos++;
  if ((dir < 0) && (shipPos > 0)) shipPos--;
}

void DrawLaser()
{
  if (laserFired == true)
    display.SetPixel(laserDistance,laserPos);

  laser.SetPos(laserFired,laserPos,laserDistance);
  laser.SetCounter(counter);
}

void FireLaser(int pos)
{
  laserFired = true;
  laserPos = pos;
  laserDistance = 0;
}

void UpdateLaser()
{
  if (laserDistance > 10)
    laserFired = false;
  else
  {
    if (laserFired == true)
      laserDistance++;
  }
}

