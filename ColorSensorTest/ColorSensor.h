// ColorSensor.h

#ifndef _COLORSENSOR_h
#define _COLORSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ColorSensorClass
{
 protected:


 public:
	void init();
};

extern ColorSensorClass ColorSensor;

#endif

