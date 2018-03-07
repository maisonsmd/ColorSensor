// ColorSensor.h

#ifndef _COLORSENSOR_h
#define _COLORSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Colors.h"

struct freq {
	uint32_t red;
	uint32_t green;
	uint32_t blue;
};

class ColorSensor
{
 private:
	 uint8_t S0_pin, S1_pin, S2_pin, S3_pin, out_pin;
	 Colors * color_set;
	 uint8_t number_of_colors = 0;

	 freq current_freq;
	 freq min_freq;
	 freq max_freq;


 public:
	ColorSensor(uint8_t S0_pin, uint8_t S1_pin, uint8_t S2_pin, uint8_t S3_pin, uint8_t out_pin);
	void addColor(const Colors color);
	freq getCurretnFreq(void);
	void execute(void);
	void calib(Colors color);
	void calibPureWhite(void);
	void calibDeepBlack(void);

	Colors getCurrentColor(void);
	Colors getMostSimilarColor(float percentage_threshold = 0);
};
#endif

