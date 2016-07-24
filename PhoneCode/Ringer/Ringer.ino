//------------------------------------------------------------------------------
//  Description:
//    This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#define led 13

boolean isRinging, ringerToggle;
long startTime, toggleTime;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println("Serial initalized");
  pinMode(led, OUTPUT);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ringPhone()
{
  if (ringerToggle && (millis() - toggleTime > 2000))
  {
    toggleTime = millis();
    ringerToggle = !ringerToggle;
  }
  if (!ringerToggle && millis() - toggleTime > 1000)
  {
    toggleTime = millis();
    ringerToggle = !ringerToggle;
  }
  if (ringerToggle)
  {
    delay(21);
    digitalWrite(led, HIGH);
    delay(21);
  }
  digitalWrite(led,LOW);

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{

  while(Serial.available())
  {
    char inputChar = Serial.read();
    delay(2);
    if (inputChar == 'r')
    {
      ringerToggle = isRinging = true;
      toggleTime = startTime = millis();
    }
    else if (inputChar == 'o')
    {
      isRinging = false;
    }
  }

  if (isRinging)
  {
    if (millis() - startTime > 10000)
    {
      startTime = millis();
      isRinging = false;
    }
    ringPhone();
  }
}

