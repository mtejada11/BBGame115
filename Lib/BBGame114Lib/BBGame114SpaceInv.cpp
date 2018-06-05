
//========== BBGAME114 SPACE INVADERS GAME LIBARY ==========

//Date: May 30, 2018


#include "BBGame114SpaceInv.h"
#include <EEPROM.h>


extern Display display;
Sound sound;
int numHits = 0;



struct Level levels[] = 
{
  {  200, 1000, 60, 1, NewAlienLevel1 },
  { 1100, 1300, 20, 2, NewAlienLevel2 },
  { 1400, 1900, 40, 4, NewAlienLevel1 },
  { 2000, 2300, 20, 8, NewAlienLevel2 },
  { 2700, 2880, 20, 8, NewAlienLevelEmpty }
};



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
  if (fired)
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


int counter2 = 0;


byte NewAlienLevel1(int counter)
{
    byte y = random(4);
    return Display::MakeBit(y);
}

byte NewAlienLevel2(int counter)
{
    byte y = (counter2++ % 2) + 1;
    return Display::MakeBit(y);
}

byte NewAlienLevelEmpty(int counter)
{
    return 0;
}

Aliens::Aliens()
{
  num = 0;
  next = 0;
  level = 0;

  //Get random numbers seed value from EEPROM location 10
  byte rndSeed;
  EEPROM.get(10, rndSeed);
  randomSeed(rndSeed);
}

void Aliens::AddAlien(int counter)
{
    Level *L = &(levels[level]);
    if (counter > L->end) 
    {
      counter2 = 0;
      level++;
    }

    L = &(levels[level]);
    if ((counter < L->start) || (counter > L->end)) return;
    
    byte i = next;
    if (num < 12) num++; 

    aliens[i] = L->NewAlienFunc(counter);
    pos[i] = 11;
    state[i] = 1;

    next++;
    next %= 12;
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


int Aliens::NextAlienInterval()
{
  return levels[level].update_interval;
}


bool Aliens::Finished()
{
  if (level >= NUM_LEVELS)
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

