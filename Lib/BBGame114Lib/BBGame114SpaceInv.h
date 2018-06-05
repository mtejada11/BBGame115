
//========== BBGAME114 SPACE INVADERS GAME LIBARY ==========

//Date: May 30, 2018


#ifndef LIBGAME_H
#define LIBGAME_H


#include "BBGame114.h"


struct Level
{
    int start;
    int end;
    int update_interval;
    byte points;
    byte (*NewAlienFunc)(int counter);
};

extern struct Level levels[];

byte NewAlienLevel1(int counter);
byte NewAlienLevel2(int counter);
byte NewAlienLevel3(int counter);
byte NewAlienLevelEmpty(int counter);

#define NUM_LEVELS 5

class Aliens
{
public:
    Aliens();
    void AddAlien(int counter);
    void Draw(Display &display);
    void Update(int counter);
    int NextAlienInterval();
    bool Finished();

    byte aliens[12];
    byte pos[12];
    byte state[12];
    byte num;
    byte next;

    byte level;
};


#define ALIEN_HIT 2


class Spaceship
{
public:
    Spaceship();
    void Draw(Display &display);
    void Move(int8_t dir);
    void CheckHit(Aliens &aliens);
    void SetPos(byte externalPos);

    byte pos;
    byte bitImage;
    byte state;
};


class Laser
{
public:
    Laser();
    void Draw(Display &display);
    void Update(int counter);
    void Fire(int shipPos);
    void CheckHit(Aliens &aliens);
    void SetPos(bool externalFired, byte externalPos, byte externalDistance);
    void SetCounter(int externalCounter);
    bool IsStillFired();
    int GetNumHits();

    bool fired;
    int8_t pos;
    int8_t distance;
    byte bitImage; //not used yet
    int counter;
};


#endif //LIBGAME_H
