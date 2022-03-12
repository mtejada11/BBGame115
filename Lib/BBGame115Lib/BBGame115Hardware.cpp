
//========== BBMATRIX54 HARDWARE LIBARY ==========

//Date: June 30, 2019

#include "BBGame115.h"


//---------- DISPLAY CLASS ----------

// Purpose: To abstract the BBGame115 LED matrix as a display, 
// with methods/functions to clear the display, draw a dot,
// draw horizontal or vertical lines and draw text.


byte displayRows[5] = { 8, 9, 11, 12, 13 };
byte displayCols[11] = { 2, 3, 4, 5, 6, 7, A5, A4, A3, A2, A1 };

byte displayBuffer[11];
int  displayCounter = 0;
byte displaySlowdownFactor = 1;
byte displayScanRow = 0;



void Display::Setup(byte _numCols, byte _numRows)
{
  numCols = _numCols;
  numRows = _numRows;
  if(numCols > 11) numCols = 11;
  if(numRows > 5)  numRows = 5;

  int i,j;
  for(i = 0; i < 11; i++) pinMode(displayCols[i], OUTPUT);
  for(j = 0; j < 5; j++)  pinMode(displayRows[j], OUTPUT);
  Clear();

  SetupTimedRefresh();
}


void Display::Clear()
{
  byte *p = displayBuffer;
  for(byte i = 0; i < numCols; i++)
    (*(p++)) = 0;
}


byte Display::MakeBit(byte y)
{
  return (1 << (4 - y));
}


byte Display::SetPixel(byte x, byte y, byte c)
{
  if ((x<0) || (x>=numCols)) return 0;
  
  byte mask = ~(16 >> y);
  byte bits = (c << (4 - y));
  noInterrupts();
  displayBuffer[x] &= mask;
  displayBuffer[x] |= bits;
  interrupts();

  return bits;
}


void Display::SetByte(byte x, byte bits)
{
  if ((x<0) || (x>=numCols)) return;
  
  noInterrupts();
  displayBuffer[x] |= bits;
  interrupts();
}


void Display::vLine(byte x, byte y1, byte y2)
{
  if (y1 == 255) y1 = 0;
  if (y2 == 255) y2 = numRows;
  for(byte i = y1; i <= y2; i++)
    SetPixel(x, i, 1);
}


void Display::hLine(byte y, byte x1, byte x2)
{
  if (x1 == 255) x1 = 0;
  if (x2 == 255) x2 = numCols;
  for(byte i = x1; i <= x2; i++)
    SetPixel(i, y, 1);
}


void Display::hShift(byte dir, bool wrap)
{
  signed char incr = (dir == 0) ? +1 : -1;
  byte *p1 = (dir == 0) ? (displayBuffer+1) : (displayBuffer+numCols-2);
  byte *p2 = p1 - incr;
  byte *p0 = p2;
  byte v0 = (wrap == false) ? 0 : (*p2);

  for(byte i = 0; i < (numCols-1); i++)
  {
    (*p2) = (*p1);
    p1 += incr;
    p2 += incr;
  }
  (*p2) = v0;
}


void Display::vShift(byte dir, bool wrap)
{
  byte shiftedOutBits;
  
  for(byte i = 0; i < numCols; i++)
  {
    if (dir == 0) 
    {
      shiftedOutBits = (displayBuffer[i] & 0x8) >> 3;
      displayBuffer[i] <<= 1;
}
    else
    {
      shiftedOutBits = (displayBuffer[i] & 0x1) << 3;
      displayBuffer[i] >>= 1;
    }

    if (wrap == true)
      displayBuffer[i] |= shiftedOutBits;  
  } 
}

void Display::SetSlowdown(byte factor)
{
  if (factor < 1) factor = 1;
  displaySlowdownFactor = factor;
}


void Display::SetupTimedRefresh()
{
  cli();//stop interrupts

  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0

  // set compare match register for 8khz increments
  OCR2A = 60;// = n / (8000*8) - 1 (must be <256)

  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS20); //100 - 64 scaler, 1 ms
  TCCR2B |= (1 << CS21); //110 - 256 scaler, 4 ms
  TCCR2B |= (1 << CS22); //111 - 1024 scaler, 16 ms

  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts
}


SIGNAL(TIMER2_COMPA_vect) 
{
  byte j = displayScanRow;
  byte on_value;

  displayCounter++;
  if ((displayCounter % displaySlowdownFactor) != 0) return;

  digitalWrite(displayRows[0], 1);
  digitalWrite(displayRows[1], 1);
  digitalWrite(displayRows[2], 1);
  digitalWrite(displayRows[3], 1);
  digitalWrite(displayRows[4], 1);
  for(byte i = 0; i < 11; i++)
    digitalWrite(displayCols[i], 0);

  digitalWrite(displayRows[j], 0);
  byte *p = displayBuffer;
  byte mask = 16 >> j; 
  for(byte i = 0; i < 11; i++)
    digitalWrite(displayCols[i], ((*(p++)) & mask) ? 1 : 0);

  noInterrupts();
  displayScanRow++;
  displayScanRow %= 5;
  interrupts();
}


//---------- BUTTONS CLASS ----------

// Purpose: To simplify the use of the pushbuttons on the 
// BBGame115 board. The BtnPressed() method/function only 
// returns true one time after a buttons is pressed, and it 
// is not reset until the button is released.


byte buttonPins[3] = { A0, A7, A6 };


void Buttons::Setup()
{
    for(byte i = 0; i < 3; i++)
    {
        pinMode(buttonPins[i], INPUT);
        btnWasNotPressed[i] = true;
    }
}


bool Buttons::BtnDown(byte i)
{
    bool BtnPressedNow = analogRead(buttonPins[i])>30;
    return BtnPressedNow;
}


bool Buttons::BtnPressed(byte i)
{
    bool BtnPressedNow = analogRead(buttonPins[i])>30;
    if(btnWasNotPressed[i] && BtnPressedNow)
    {
      btnWasNotPressed[i] = false;
      return true;
    }
    else
    {
      if(!BtnPressedNow)
        btnWasNotPressed[i] = true;
      return false;
    }
}


//---------- SOUND CLASS ----------

// Purpose: To output sound tones through the piezoelectric
// speaker on the the BBGame115 board.


void Sound::Setup()
{
  pinMode(SNDPIN,OUTPUT);
  tone = 0;
  duration = 0;
  noisy = false;
}


void Sound::Update(int counter)
{
  if (duration > 0)
  {
    duration--;
    analogWrite(SNDPIN,tone);
    if (noisy && (counter%2 == 0)) 
      analogWrite(SNDPIN,0);
  }
  else
    analogWrite(SNDPIN,0);    
}


void Sound::StartSound(byte _tone, byte _duration, bool _noisy)
{
  tone = _tone;
  duration = _duration;
  noisy = _noisy;
}


//---------- TEXTDISPLAY CLASS ----------

// Purpose: To draw alphanumeric characters and punctuation on the
// BBGame115 display.


TextDisplay::TextDisplay(Display& _display):
  display(_display)
{
}


void TextDisplay::DisplayText(String s, int pos)
{
  byte n = s.length();
  byte np = GetWidth(s);
  byte const *p;

  for(byte i=0; i< n; i++)
  {
    GetCharPixelData(s[i],&np,&p);
    for(byte j=0; j<np; j++)
    {
      display.SetByte(pos+j, pgm_read_byte_near(p+j));
    }
    pos += np;
    if (i < (n-1)) pos += 1;
  }
}


void TextDisplay::DisplayTextCentered(String s)
{
  byte np = GetWidth(s);
  int pos = (display.numCols - np) / 2;
  if (pos < 0) pos = 0;
  DisplayText(s, pos);
}


int TextDisplay::GetWidth(String s)
{
  byte n = s.length();
  byte np;
  byte const *p;

  int pos = 0;
  for(int i = 0; i < n; i++)
  {
    GetCharPixelData(s[i],&np,&p);
    pos += np;
    if (i < (n-1)) pos += 1;
  }

  return pos;
}


void TextDisplay::ScrollText(String s, int counter)
{
  int pos = display.numCols - (counter % getScrollWidth(s));
  display.Clear();
  DisplayText(s, pos);
}


int TextDisplay::getScrollWidth(String s)
{
  int width = display.numCols + GetWidth(s) + display.numCols;
  return width;
}


const byte PROGMEM font3x5[] = 
{
3, 0x00, 0x00, 0x00, 0x00, 0x00, // (space)
1, 0x1D, 0x00, 0x00, 0x00, 0x00, // !
2, 0x18, 0x18, 0x00, 0x00, 0x00, // "
4, 0x0A, 0x1F, 0x1F, 0x0A, 0x00, // #
3, 0x0A, 0x1F, 0x0A, 0x00, 0x00, // $
3, 0x12, 0x04, 0x09, 0x00, 0x00, // %
3, 0x0A, 0x15, 0x17, 0x00, 0x00, // &
1, 0x18, 0x00, 0x00, 0x00, 0x00, // '
2, 0x0E, 0x11, 0x00, 0x00, 0x00, // (
2, 0x11, 0x0E, 0x00, 0x00, 0x00, // )
3, 0x0A, 0x04, 0x0A, 0x00, 0x00, // *
3, 0x04, 0x0E, 0x04, 0x00, 0x00, // +
2, 0x01, 0x02, 0x00, 0x00, 0x00, // ,
3, 0x04, 0x04, 0x04, 0x00, 0x00, // -
1, 0x01, 0x00, 0x00, 0x00, 0x00, // .
4, 0x01, 0x02, 0x04, 0x08, 0x00, // /

3, 0x0E, 0x11, 0x0E, 0x00, 0x00, // 0
2, 0x08, 0x1F, 0x00, 0x00, 0x00, // 1
3, 0x13, 0x15, 0x09, 0x00, 0x00, // 2
3, 0x11, 0x15, 0x0A, 0x00, 0x00, // 3
3, 0x1C, 0x04, 0x1F, 0x00, 0x00, // 4
3, 0x1D, 0x15, 0x12, 0x00, 0x00, // 5
3, 0x0E, 0x15, 0x16, 0x00, 0x00, // 6
3, 0x10, 0x17, 0x18, 0x00, 0x00, // 7
3, 0x0A, 0x15, 0x0A, 0x00, 0x00, // 8
3, 0x0C, 0x15, 0x0E, 0x00, 0x00, // 9

1, 0x0A, 0x00, 0x00, 0x00, 0x00, // :
2, 0x01, 0x0A, 0x00, 0x00, 0x00, // ;
2, 0x04, 0x0A, 0x00, 0x00, 0x00, // <
3, 0x0A, 0x0A, 0x0A, 0x00, 0x00, // =
2, 0x0A, 0x04, 0x00, 0x00, 0x00, // >
3, 0x10, 0x15, 0x08, 0x00, 0x00, // ?
3, 0x0E, 0x15, 0x0D, 0x00, 0x00, // @

3, 0x0F, 0x14, 0x0F, 0x00, 0x00, // A
3, 0x1F, 0x15, 0x0A, 0x00, 0x00, // B
3, 0x0E, 0x11, 0x11, 0x00, 0x00, // C
3, 0x1F, 0x11, 0x0E, 0x00, 0x00, // D
3, 0x1F, 0x15, 0x15, 0x00, 0x00, // E
3, 0x1F, 0x14, 0x14, 0x00, 0x00, // F
3, 0x0E, 0x11, 0x17, 0x00, 0x00, // G
3, 0x1F, 0x04, 0x1F, 0x00, 0x00, // H
1, 0x1F, 0x00, 0x00, 0x00, 0x00, // I
3, 0x01, 0x01, 0x1E, 0x00, 0x00, // J
3, 0x1F, 0x04, 0x1B, 0x00, 0x00, // K
3, 0x1F, 0x01, 0x01, 0x00, 0x00, // L
3, 0x1F, 0x0C, 0x1F, 0x00, 0x00, // M
 
3, 0x1F, 0x10, 0x0F, 0x00, 0x00, // N
3, 0x0E, 0x11, 0x0E, 0x00, 0x00, // O
3, 0x1F, 0x14, 0x08, 0x00, 0x00, // P
3, 0x0E, 0x11, 0x0F, 0x00, 0x00, // Q
3, 0x1F, 0x14, 0x0B, 0x00, 0x00, // R
3, 0x09, 0x15, 0x12, 0x00, 0x00, // S
3, 0x10, 0x1F, 0x10, 0x00, 0x00, // T
3, 0x1E, 0x01, 0x1E, 0x00, 0x00, // U
3, 0x1E, 0x03, 0x1E, 0x00, 0x00, // V
3, 0x1F, 0x06, 0x1F, 0x00, 0x00, // W
3, 0x1B, 0x04, 0x1B, 0x00, 0x00, // X
3, 0x18, 0x07, 0x18, 0x00, 0x00, // Y
3, 0x13, 0x15, 0x19, 0x00, 0x00, // Z
 
2, 0x1F, 0x11, 0x09, 0x00, 0x00, // [
4, 0x08, 0x04, 0x02, 0x01, 0x00, // \
2, 0x11, 0x1F, 0x00, 0x00, 0x00, // ]
3, 0x08, 0x10, 0x08, 0x00, 0x00, // ^
3, 0x01, 0x01, 0x01, 0x00, 0x00, // _
};


void TextDisplay::GetCharPixelData(char c, byte *np, byte const **p)
{
  int index = 0;
  if((c >= ' ') && (c <= '_'))
    index = c - ' ';
  else if((c >= 'a') && (c <= 'z'))
    index = c - 'a' + 33;
  else
    index = 0;
  index *= 6;
  (*np) = pgm_read_byte_near(font3x5+index);
  (*p) = font3x5 + index + 1;
}
