
//========== BBGAME115 SPACE INVADERS GAME LIBARY ==========

//Date: May 30, 2018


#ifndef LIBGAME_H
#define LIBGAME_H


#include "BBGame115.h"


typedef struct
{
    int start_delay;
    int duration;
    int update_interval;
    int add_interval;
    byte type;
    byte min;
    byte max;
    byte points;
    int start;
    int end;
} 
GameLevel;

typedef enum 
{ 
    ALIENWAVE_RANDOM = 0,
    ALIENWAVE_MARCH = 1,
    ALIENWAVE_END = 2      
} 
AlienWaveType;


byte NewAlienLevel1(int counter);
byte NewAlienLevel2(int counter);
byte NewAlienLevel3(int counter);
byte NewAlienLevelEmpty(int counter);


class Aliens
{
public:
    Aliens();
    void AddAlien(int counter);
    void Draw(Display &display);
    void Update(int counter);
    int NextAlienInterval();
    bool Finished();
    void SetGameLevels(GameLevel *newLevels);

    byte aliens[12];
    byte pos[12];
    byte state[12];
    byte num;
    byte next;

    byte numLevels;
    byte level;

private:
    GameLevel *levels;
    void AdjustGameLevelGaps(GameLevel *newLevels);
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
