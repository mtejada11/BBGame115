#include "BBGame115.h"
#include "BBGame115Other.h"

extern Display display;
extern Buttons buttons;
extern TextDisplay textDisplay;


//---------- Count up to 100 and down to 0 ----------

void CountUpandDown(int maxCount)
{
  int d = 150;
  while(true)
  {
    delay(d);
    for(int i = 0; i <= maxCount; i++)
    {
      display.Clear();
      textDisplay.DisplayTextCentered(String(i));
      delay(d);
    }
    delay(d);
    for(int i = maxCount; i >= 0; i--)
    {
      display.Clear();
      textDisplay.DisplayTextCentered(String(i));
      delay(d);
    }
  }
}


//---------- Scroll name ----------

void ScrollName(char *name)
{
  int counter = 0;
  while(true)
  {
    textDisplay.ScrollText(name, counter);
    delay(75);
    counter++;
  }
}
