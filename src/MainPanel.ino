//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
int led = 13;

int ledMap[4][5] = {{ 3,  4,  9,  8, 34},
                    {37, 28, 38, 33, 22},
                    {36, 39, 32, 30, 41},
                    {26, 40, 35, 24, 7 }};

int switchMap[4][5] = {{42, 50, 44, 45, 11},
                       {21, 47, 49, 48, 2},
                       {43, 17, 20, 51, 10},
                       {19, 52, 46, 53,  5}};

#define numInverted 3
int invertedSwitches[numInverted] = {11, 2, 10};

boolean switchStates[4][5];


void getSwitchStates();
void writeLeds();

void offMode();
void randomPartyMode();
void toggleFlipMode();
void writeLeds();
void serialSwitchStates();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; ++j)
    {
      pinMode(ledMap[i][j], OUTPUT);
      pinMode(switchMap[i][j], INPUT_PULLUP);
      digitalWrite(ledMap[i][j], LOW);
      switchStates[i][j] = digitalRead(switchMap[i][j]);
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void serialSwitchStates()
{
  Serial.println();
  Serial.println();
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; ++j)
    {
      Serial.print(switchStates[i][j]);
      Serial.print(", ");
    }
      Serial.println();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
boolean isInverted(int pinValue)
{
  boolean inverted = false;
  for (int i = 0; i < numInverted; ++i)
  {
    if (pinValue == invertedSwitches[i])
    {
      return true;
    }
  }
  return inverted;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void getSwitchStates()
{
  int pinValue;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; ++j)
    {
      pinValue = switchMap[i][j];
      if(isInverted(pinValue))
      {
        switchStates[i][j] = !digitalRead(switchMap[i][j]);
      }
      else
      {
        switchStates[i][j] = digitalRead(switchMap[i][j]);
      }
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void writeLeds()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; ++j)
    {
        digitalWrite(ledMap[i][j], switchStates[i][j]);
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void offMode()
{
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 5; ++j)
    {
      digitalWrite(ledMap[i][j], LOW);
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{
  getSwitchStates();
  writeLeds();
}
