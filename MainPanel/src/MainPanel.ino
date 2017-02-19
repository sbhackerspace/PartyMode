//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Description:
//    This is the control code for the large panel of the emergency party button
//
//  Authors: Mike Kapuscik, Dan Loman
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "ControlPanel.h"
//#include "TestPanel.h"
#include "Ring.h"

Ring ring;
ControlPanel panel(ring);
//TestPanel panel(ring);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  panel.setupPanel();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop()
{
  panel.run();
}
