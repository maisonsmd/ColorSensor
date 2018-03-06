#include "ColorSensor.h"
#include "Colors.h"
void setup()
{
	Serial.begin(115200);
}

void loop()
{
	RGB rgb(255, 56, 4);
	HSV hsv(69, 45, 76);
	Serial.println(rgb.toHSV().toRGB().toHSV().toString());
	delay(500);
}
