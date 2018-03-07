// 
// 
// 

#include "ColorSensor.h"

ColorSensor::ColorSensor(uint8_t S0_pin, uint8_t S1_pin, uint8_t S2_pin, uint8_t S3_pin, uint8_t out_pin)
{
	this->S0_pin = S0_pin;
	this->S1_pin = S1_pin;
	this->S2_pin = S2_pin;
	this->S3_pin = S3_pin;
	this->out_pin = out_pin;
	pinMode(S0_pin, OUTPUT);
	pinMode(S1_pin, OUTPUT);
	pinMode(S2_pin, OUTPUT);
	pinMode(S3_pin, OUTPUT);
	pinMode(out_pin, INPUT);
	//20% scale freq
	digitalWrite(S0_pin, HIGH);
	digitalWrite(S1_pin, LOW);
}

void ColorSensor::addColor(const Colors color)
{
	number_of_colors++;
	Colors * temp = new Colors[number_of_colors];
	for (uint8_t i = 0; i < number_of_colors - 1; i++)
		temp[i] = color_set[i];
	if (color_set != nullptr)
		delete[] color_set;
	color_set = temp;
	color_set[number_of_colors - 1] = color;
}

freq ColorSensor::getCurretnFreq(void)
{
	return current_freq;
}

void ColorSensor::execute(void)
{
	const uint32_t GET_VALUES_PERIOD = 5;
	static uint8_t color_handling = 0; // 0 = red, 1 = green, 2 = blue;
	static uint32_t timerGetValues = 0;

	if (timerGetValues > millis())
		timerGetValues = millis();

	if (millis() - timerGetValues > GET_VALUES_PERIOD)
	{
		timerGetValues = millis();
		switch (color_handling)
		{
		case 0:
			digitalWrite(S2_pin, LOW);
			digitalWrite(S3_pin, LOW);

			current_freq.red = pulseIn(out_pin, LOW);
			if (current_freq.red == 0)
				current_freq.red = 3000;

			color_handling = 1;
			break;
		case 1:
			digitalWrite(S2_pin, HIGH);
			digitalWrite(S3_pin, HIGH);

			current_freq.green = pulseIn(out_pin, LOW);
			if (current_freq.green == 0)
				current_freq.green = 3000;
			color_handling = 2;
			break;
		case 2:
			digitalWrite(S2_pin, LOW);
			digitalWrite(S3_pin, HIGH);
			current_freq.blue = pulseIn(out_pin, LOW);
			if (current_freq.blue == 0)
				current_freq.blue = 3000;
			color_handling = 0;
			break;
		}
	}
}

void ColorSensor::calibPureWhite(void)
{
	uint32_t preCount = millis();
	while (millis() - preCount < 500)
		execute();
	max_freq = current_freq;
}

void ColorSensor::calibDeepBlack(void)
{
	uint32_t preCount = millis();
	while (millis() - preCount < 500)
		execute();
	min_freq = current_freq;
}

Colors ColorSensor::getCurrentColor(void)
{
	float red = map(current_freq.red, min_freq.red, max_freq.red, 0, 255);
	float green = map(current_freq.green, min_freq.green, max_freq.green, 0, 255);
	float blue = map(current_freq.blue, min_freq.blue, max_freq.blue, 0, 255);
	return Colors(RGB(red, green, blue));
}

