#include "Panel.h"

const int Panel::keySwitch = 6;
const int Panel::keyLed = 14;
const int Panel::redSwitch = 15;
const int Panel::redLed	= 12;
const int Panel::knobPin = A9;

const int Panel::toggleMap[4][4] = {{42, 50, 44, 45},
                       				{21, 47, 49, 48},
                       				{43, 17, 20, 51},
                       				{19, 52, 46, 53}};

const int Panel::toggleLeds[4][4] = {{ 3,  9,  4,  8},
                        			 {37, 28, 38, 33},
                        			 {36, 39, 32, 30},
                        			 {26, 40, 35, 24}};

const int Panel::sideSwitches[4] = {11, 2, 10, 5};
const int Panel::sideLeds[4] = {34, 22, 41, 7};
const int Panel::invertedSwitches[numInvertedSwitches] = {15, 42, 50, 44, 45, 11, 2, 10};

Panel::Panel(void){
	keyState = false;
	redState = false;


}


