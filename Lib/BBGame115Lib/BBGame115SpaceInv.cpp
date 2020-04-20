
//========== BBGAME115 SPACE INVADERS GAME LIBARY ==========

//Date: May 30, 2018


#include "BBGame115SpaceInv.h"
#include <EEPROM.h>


extern Display display;
Sound sound;
int numHits = 0;


//---------- SPACESHIP CLASS ----------

// Purpose: To implement a spaceship that moves up and down on the
// left side of the display area.


Spaceship::Spaceship()
{
    pos = 2;
    bitImage = 0;
    state = 1;
}


void Spaceship::Draw(Display &display)
{
    byte a = Display::MakeBit(pos);
    
    switch(state)
    {
    case 1://Normal
      display.SetPixel(0,pos,1);
      bitImage = display.SetPixel(1,pos,1);
      break;

    case 2:
    case 4:
    case 6:
      //Explosion 1
      //display.SetByte(0, (a<<1)|(a>>1));
      //display.SetByte(1, (a<<1)|(a>>1));
      //display.SetByte(2, a);
      state++;
      break;

    case 3:
    case 5:
      //Explosion 2
      display.SetByte(0,a);
      display.SetByte(1,a);
      state++;
      break;

    case 0:
    default:
      state = 1;
      break;
    }
}


void Spaceship::Move(int8_t dir)
{
  if((dir==+1) && (pos < 3)) pos++;
  if((dir==-1) && (pos > 0)) pos--;
}


void Spaceship::CheckHit(Aliens &aliens)
{
  if (state != 1) return;
  
  for(byte i=0; i<aliens.num; i++)
  {
    if (aliens.state[i]==1)
    {
      if ((aliens.pos[i] <= 1) && (aliens.aliens[i] & bitImage))
      {
        state = 2;
        aliens.state[i] = 0;
        aliens.pos[i] = 11;
        //sound.StartSound(60, 10); //spaceship hit
      }
    }
  }
}


void Spaceship::SetPos(byte externalPos)
{
  pos = externalPos;
}


//---------- LASER CLASS ----------

// Purpose: To implement a firing laser that starts at the position
// of the spaceship and rapidly moves across the display area. A function
// for collision detection the the Aliens class is also implemented.


Laser::Laser()
{
    fired = false;
    pos = -1;
    distance = -1;
    bitImage = 0;
    counter = 0;
    sound.Setup();
}


void Laser::Draw(Display &display)
{
  if (fired)
    bitImage = display.SetPixel(distance,pos,1);
}


void Laser::Update(int counter_)
{
  counter = counter_;

  if(distance > 10)
  {
      fired = false;
      return;
  } 

  if(counter%1==0)
  {
    if(fired) distance++;
  }
}


void Laser::Fire(int shipPos)
{
  if(!fired)
  {
    fired = true;
    distance = 0;
    pos = shipPos;
    sound.StartSound(120, 5);
  }
}


void Laser::CheckHit(Aliens &aliens)
{
  if (fired && (distance >= 2))
  {
    for(byte i=0; i<aliens.num; i++)
      if((aliens.pos[i]==distance) && (aliens.state[i]!=0))
      {
        if(bitImage & aliens.aliens[i])
        {
          aliens.state[i] = ALIEN_HIT;
          pos = 11;
          fired = false;
          sound.StartSound(200, 15, true); //alien explosion
          numHits++;
        }
      }
  }

  //Also take care of sound update here, because this is always called
  sound.Update(counter);
}


void Laser::SetPos(bool externalFired, byte externalPos, byte externalDistance)
{
  fired = externalFired;
  pos = externalPos;
  distance = externalDistance;
  bitImage = display.MakeBit(pos);

  if ((fired == true) && (distance == 0))
    sound.StartSound(120, 5);
}


void Laser::SetCounter(int externalCounter)
{
  counter = externalCounter;
}


bool Laser::IsStillFired()
{
  return fired;
}


int Laser::GetNumHits()
{
  return numHits;
}


//---------- ALIENS CLASS ----------

// Purpose: To implement an object that creates game levels with waves
// of aliens moving across the display.


// ----- Game levels with different waves of aliens -----

GameLevel defaultGameLevels[] = 
{
  { 150, 700, 20, 40, ALIENWAVE_RANDOM, 0, 3, 2 },
  { 200, 200, 20, 20, ALIENWAVE_MARCH,  1, 2, 1 },
  { 200, 500, 20, 40, ALIENWAVE_RANDOM, 0, 3, 2 },
  { 200, 200, 15, 15, ALIENWAVE_MARCH,  1, 2, 1 },
  { 200, 300, 15, 30, ALIENWAVE_RANDOM, 0, 3, 2 },
  {  50, 0,   0 ,  0, ALIENWAVE_END,    0, 0, 0 }
};

int counter2 = 0;


// ----- Aliens class methods -----

Aliens::Aliens()
{
  num = 0;
  next = 0;
  level = 0;

  numLevels = 0;
  SetGameLevels(defaultGameLevels);

  //Get random numbers seed value from EEPROM location 10
  byte rndSeed;
  EEPROM.get(10, rndSeed);
  randomSeed(rndSeed);
}


void Aliens::Draw(Display &display)
{
  for(byte i=0; i<num; i++)
  {
    if(state[i] != 0)
    {
      byte a = aliens[i];
      switch(state[i])
      {
      case 1://Normal
        display.SetByte(pos[i],a);
        break;

      case 2:
      case 4:
      case 6:
        //Explosion 1
        display.SetByte(pos[i]-1, a);
        display.SetByte(pos[i], (a<<1)|(a>>1));
        display.SetByte(pos[i]+1, a);
        state[i]++;
        break;

      case 3:
      case 5:
        //Explosion 2
        display.SetByte(pos[i],a);
        state[i]++;
        break;

      case 0:
      default:
        state[i] = 0;
        pos[i] = 11;
        break;
      }
    }
    display.SetByte(pos[i],aliens[i]);
  }
}


void Aliens::Update(int counter)
{
  if ((counter > levels[level].end) && (counter >= levels[level+1].start))
  {
    counter2 = 0;
    level++;
  }

  if ((counter % levels[level].update_interval) == 0)
  {
    for(byte i=0; i<num; i++)
    {
      if(state[i]==1)
      {
          if(pos[i]>=0) 
              pos[i]--;
          else
          {
              pos[i] = 11;
              state[i] = 0;
          }
      }
    }
  }
}


byte NewAlienRandom(int counter, byte min, byte max)
{
    byte y = random(max-min+1) + min  ;
    return Display::MakeBit(y);
}


byte NewAlienMarch(int counter, byte min, byte max)
{
    byte y = 3 - ((counter2++ % (max-min+1)) + min);
    return Display::MakeBit(y);
}


void Aliens::AddAlien(int counter)
{
    GameLevel *L = &(levels[level]);

    if (counter > L->end) return;

    L = &(levels[level]);
    if ((counter < L->start) || (counter > L->end)) return;
    
    byte i = next;
    if (num < 12) num++; 

    aliens[i] = 0;
    state[i] = 0;
    if (L->type == ALIENWAVE_RANDOM) 
    {
      aliens[i] = NewAlienRandom(counter,L->min,L->max);
      pos[i] = 11;
      state[i] = 1;
    }
    if (L->type == ALIENWAVE_MARCH) 
    {
      aliens[i] = NewAlienMarch(counter,L->min,L->max);
      pos[i] = 11;
      state[i] = 1;
    }

    next++;
    next %= 12;
}


int Aliens::NextAlienInterval()
{
  return levels[level].add_interval;
}


void Aliens::SetGameLevels(GameLevel *newLevels)
{
  levels = newLevels;
  int current_time = 0;

  int i = 0;
  do
  {
    levels[i].start = current_time + levels[i].start_delay;
    levels[i].end = levels[i].start + levels[i].duration;
    current_time = levels[i].end;
    if (levels[i].add_interval < levels[i].update_interval) levels[i].add_interval = levels[i].update_interval;
    i++;
  }
  while(levels[i-1].type != ALIENWAVE_END);
  numLevels = i;

  AdjustGameLevelGaps(levels);
}


void Aliens::AdjustGameLevelGaps(GameLevel *newLevels)
{
  for(byte i = 0; i < (numLevels-1); i++)
  {
    //If update interval is different...
    if(levels[i].update_interval != levels[i+1].update_interval)
    {
      //Calculate adjustment needed in gap
      int gap = levels[i+1].start - levels[i].end;
      int neededGap = levels[i].update_interval * 12;

      //For any insufficient gap or for last wave...
      if((gap < neededGap) || (i == (numLevels-2)))
      {
        //Adjust all subsequent gaps
        int gapAdjustment = neededGap - gap;
        for(byte j = i+1; j < numLevels; j++)
        {
          levels[j].start += gapAdjustment;
          levels[j].end += gapAdjustment;
        }
      }
    }
  }
}


bool Aliens::Finished()
{
  if (level >= numLevels)
  {
    //Put score in EEPROM location 10 for next power up
    EEPROM.put(10, (byte)numHits);

    //Return true to indicate game is done
    return true;
  }
  else
  {
    //Return false to indicate game is not done yet
    return false;
  }
}

