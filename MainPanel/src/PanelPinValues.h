//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Description:
//    This header contains the pin mapping for the Main panel
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "Panel.h"

const int Panel::mLeftKeyPin = 18;
const int Panel::mLeftKeyLed = A8;
const int Panel::mRightKeyPin = 6;
const int Panel::mRightKeyLed = 14;
const int Panel::mRedButtonPin = 15;
const int Panel::mRedLed	= 12;
const int Panel::mKnobPin = A9;
const int Panel::mMainPowerSwitch = A13;
const int Panel::mSirenPin = 13;
const int Panel::mPhoneRingerPin = A6;

const int Panel::mToggleMap[4][4] = {{42, 50, 44, 45},
                       				{21, 47, 49, 48},
                       				{43, 17, 20, 51},
                       				{19, 52, 46, 53}};

const int Panel::mToggleLeds[4][4] = {{ 3,  9,  4,  8},
                        			 {37, 28, 38, 33},
                        			 {36, 39, 32, 30},
                        			 {26, 40, 35, 24}};

const int Panel::mSideSwitches[4] = {11, 2, 10, 5};
const int Panel::mSideLeds[4] = {34, 22, 41, 7};
const int Panel::mInvertedSwitches[numInvertedSwitches] =
  {6, 15, 11, 2, 10, 5, 18};
