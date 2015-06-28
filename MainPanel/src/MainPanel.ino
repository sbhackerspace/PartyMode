//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int keySwitch = 6;
int keyLed = 14;
boolean keyState = false;

int redSwitch = 15;
int redLed = 12;
boolean redState = false;

int knobPin = A9;

int ledMap[4][5] = {{ 3,  9,  4,  8, 34},
                    {37, 28, 38, 33, 22},
                    {36, 39, 32, 30, 41},
                    {26, 40, 35, 24, 7 }};

int switchMap[4][5] = {{42, 50, 44, 45, 11},
                       {21, 47, 49, 48, 2},
                       {43, 17, 20, 51, 10},
                       {19, 52, 46, 53,  5}};

#define numInvertedSwitches 7
int invertedSwitches[numInvertedSwitches] = {42, 50, 44, 45, 11, 2, 10};

boolean switchStates[4][5];

void setupSwitchLed(int Switch, int Led);

void getSwitchStates();
void readAnalog();
void writeLeds();

void offMode();
void randomPartyMode();
void toggleFlipMode();
void writeLeds();
void serialSwitchStates();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setupSwitchLed(int Switch, int Led)
{
  pinMode(Switch, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  digitalWrite(Led, LOW);
}

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
  setupSwitchLed(keySwitch, keyLed);
  setupSwitchLed(redSwitch, redLed);
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
  for (int i = 0; i < numInvertedSwitches; ++i)
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
  keyState = digitalRead(keySwitch);
  redState = digitalRead(redSwitch);
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
  digitalWrite(keyLed, keyState);
  digitalWrite(redLed, redState);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readAnalog()
{
  int knobValue = analogRead(knobPin);
  knobValue = map(knobValue, 0, 1024, 0, 255);
  Serial.print("knobValue = ");
  Serial.println(knobValue);
  Serial.println();
  analogWrite(13, knobValue);
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
  readAnalog();
}
