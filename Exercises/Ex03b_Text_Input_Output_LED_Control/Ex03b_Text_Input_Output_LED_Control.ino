
//========== SEED Electronics/Coding Workshop Exercise 3b ==========

//Purpose: Serial text communication between Arduino and computer for
//         controlling LEDs with keyboard input
//Date: May 28, 2018


//--- Constant definitions ---
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6

//---------- Setup routine to run once ----------

void setup() 
{

  //Set up pins to use
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
  
  //Serial communication with computer over USB
  Serial.begin(115200);
}


//----- Global variable -----
int userInputNumber;


//---------- Loop routine that runs repeatedly ----------

void loop() 
{
  //Print to computer on Arduino Serial Monitor
  Serial.println();
  Serial.println();
  Serial.println("Hello!");
  Serial.println("Let's control your LEDs using your keyboard.");

  //Get LED value input on computer as an integer
  Serial.print("Enter the LED you wish to turn on or enter 0 to turn LEDs off: ");
  userInputNumber = getIntegerInput();

  LEDControl(userInputNumber);
  
  Serial.println("Press any key to continue");

  //wait for user to type a character
  while(true)
  {
    if(Serial.available() > 0)
    {
        byte dummmyread = Serial.read();
        break;
    }
  }
}


//---------- Function getIntegerInput  ----------

//Function to check if bytes are coming in through serial connection, 
//then read those bytes in as an integer 

int getIntegerInput()
{
  //Wait until bytes come in through serial connection
  while (Serial.available() == 0) delay(100);

  //Get incoming bytes and interpret as an integer  
  int x = Serial.parseInt();

  if(x > 5 || x < 0)
  {
      Serial.print(x);
      Serial.println(", is an invalid input.");
      x = 99;
  }
  else
  {
      Serial.println(x);
  }

  //Read incoming bytes until end of line Enter character is read
  while (Serial.available() > 0) Serial.read();

  //Return integer value to the calling function
  return x;
}

//---------- Function LEDControl  ----------

//Function to control LED power based on user input

void LEDControl (int LEDNumber)
{
    
    switch(LEDNumber)
    {
        case 0:
            digitalWrite(LED1,LOW);
            digitalWrite(LED2,LOW);
            digitalWrite(LED3,LOW);
            digitalWrite(LED4,LOW);
            digitalWrite(LED5,LOW);
            Serial.println("Input 0");
            break;
        case 1:
            digitalWrite(LED1,HIGH);
            Serial.println("One");
          break;
        case 2:
            digitalWrite(LED2,HIGH);
            Serial.println("Two");
            break;
        case 3:
            digitalWrite(LED3,HIGH);
            Serial.println("Three");
            break;
        case 4:
            digitalWrite(LED4,HIGH);
            Serial.println("Four");
            break;
        case 5:
            digitalWrite(LED5,HIGH);
            Serial.println("Five");
            break;
        default:
            Serial.println("Please enter a value between 0 and 5.");
    }
}

