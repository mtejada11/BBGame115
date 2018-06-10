
//========== BBGAME114 SPACE INVADERS GAME ==========

//Date: June 2, 2018  


#include "BBGame114.h"
Display display;
Buttons buttons;
TextDisplay textDisplay(display);

#include "BBGame114SpaceInv.h"
Spaceship ship;
Laser laser;
Aliens aliens;


//---------- Setup routine to run once ----------

void setup() 
{
  display.Setup(11, 4);
  buttons.Setup();
}


//--- Global variables ---

int counter = 0;
int d = 20;

int numShips = 5;
int score = 0;
bool scoreDisplayed = false;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  if ((numShips > 0) && !aliens.Finished())
  {
    display.Clear();
    ship.Draw(display);
    laser.Draw(display);
    aliens.Draw(display);

    laser.Update(counter);
    laser.CheckHit(aliens);
    ship.CheckHit(aliens);
    aliens.Update(counter);
    
    if ((counter % aliens.NextAlienInterval()) == 0) 
      aliens.AddAlien(counter);

    if(buttons.BtnPressed(BTN1)) laser.Fire(ship.pos);     
    if(buttons.BtnPressed(BTN2)) ship.Move(+1);
    if(buttons.BtnPressed(BTN3)) ship.Move(-1);
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

