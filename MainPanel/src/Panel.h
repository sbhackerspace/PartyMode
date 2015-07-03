#ifndef _PANEL_H_
#define _PANEL_H_

#include <Arduino.h>

#define numInvertedSwitches 8

class Panel{
public:
	static const int keySwitch, keyLed, redSwitch, redLed, knobPin;
	static const int toggleMap[4][4];
	static const int toggleLeds[4][4];
	static const int sideSwitches[4];
	static const int sideLeds[4];
	static const int invertedSwitches[numInvertedSwitches];
	boolean sideStates[4];
	boolean toggleStates[4][4];
	boolean keyState, redState;

	Panel();

};





#endif
