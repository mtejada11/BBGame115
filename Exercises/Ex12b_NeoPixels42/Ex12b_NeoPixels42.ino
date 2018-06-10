
//========== SEED Electronics/Coding Workshop Exercise 12 ==========

//Purpose: Set different colors on "NeoPixel" P9823F5 or WS2811 LED
//Date: June 6, 2018

//Based on Adafruit NeoPixel sample program "simple.ino"
//NeoPixel Ring simple sketch (c) 2013 Shae Erisson


//--- Constant definitions ---
#define NEOPIXEL_DATA_PIN 12


//Use Adafruit NeoPixel library to create NeoPixel driver object
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel colorLED = Adafruit_NeoPixel(1, NEOPIXEL_DATA_PIN, NEO_RGB + NEO_KHZ800);


//---------- Setup routine to run once ----------

void setup() 
{
  //Set pin D10 to GND and output +5V on pin D11
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);

  //Setup and initialize NeoPixel driver object
  pinMode(NEOPIXEL_DATA_PIN,OUTPUT);
  colorLED.begin();
  colorLED.show();
}


//--- Global variables ---
int d = 1000;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Set LED to blue color
  colorLED.setPixelColor(0, colorLED.Color(0,10,50));
  colorLED.show();
  delay(d);

  //Set LED to orange color
  colorLED.setPixelColor(0, colorLED.Color(50,25,5));
  colorLED.show();
  delay(d);

  //Set LED to white color
  colorLED.setPixelColor(0, colorLED.Color(50,50,50));
  colorLED.show();
  delay(d);
}

