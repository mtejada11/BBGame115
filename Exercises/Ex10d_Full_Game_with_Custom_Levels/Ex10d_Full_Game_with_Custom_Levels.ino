 
//========== SEED Electronics/Coding Workshop Exercise 10d ==========

//Purpose: Full game with score display and custom game levels
//Date: June 9, 2018  


#include "BBGame114.h"
Display display;
Buttons buttons;
TextDisplay textDisplay(display);

#include "BBGame114SpaceInv.h"
Spaceship ship;
Laser laser;
Aliens aliens;

GameLevel gameLevels[] = 
{
  { 150, 400, 15, 30, ALIENWAVE_RANDOM, 0, 3, 2 },
  { 200, 100, 15, 15, ALIENWAVE_MARCH,  1, 2, 1 },
  { 200, 200, 15, 30, ALIENWAVE_RANDOM, 0, 3, 2 },
  { 200, 100,  5,  5, ALIENWAVE_MARCH,  1, 2, 1 },
  { 200, 300, 10, 20, ALIENWAVE_RANDOM, 0, 3, 2 },
  {  50, 0,   0 ,  0, ALIENWAVE_END,    0, 0, 0 }
};


//---------- Setup routine to run once ----------

void setup()
{
  display.Setup(11, 4); 
  buttons.Setup();
  aliens.SetGameLevels(gameLevels);
}


//--- Global variables ---

int counter = 0;
int d = 20;

int shipPos = 2;
int laserPos = 0;
int laserDistance = 0;
bool laserFired = false;

int numShips = 5;
int score = 0;
bool scoreDisplayed = false;


//---------- Loop routine that runs repeatedly ----------

void loop()
{
  if ((numShips > 0) && !aliens.Finished())
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

    if(buttons.BtnPressed(BTN1)) FireLaser(shipPos); 
    if(buttons.BtnPressed(BTN2)) MoveSpaceship(+1);
    if(buttons.BtnPressed(BTN3)) MoveSpaceship(-1);
  }
  else if (scoreDisplayed == false)
  {
    display.Clear();
    score = laser.GetNumHits();
    textDisplay.DisplayTextCentered(String(score));
    scoreDisplayed = true;
  }

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

