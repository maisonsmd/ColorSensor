#include "ColorSensor.h"
#include "Colors.h"
///*
ColorSensor TCS(PA1, PA2, PA4, PA5, PA3);

void setup()
{
	Serial.begin(115200);
	while (millis() < 10)
		Serial.println(millis());

	Colors c1, c2;

	Serial.println("-------------------------");
	c1.setColor(RGB(218, 72, 24));
	c1.setColor(RGB(217, 72, 24));

	Serial.println(c1.getRGB().toString());
	Serial.println(c1.getHSV().toString());
	Serial.println(c1.getHSL().toString());

	Serial.println(c2.matches(c1));
}

void loop()
{
	TCS.execute();

	static uint32_t t = 0;
	if (millis() - t > 10)
	{
		t = millis();
		/*freq f;
		f = TCS.getCurretnFreq();
		Serial.print(f.red);
		Serial.print('\t');
		Serial.print(f.green);
		Serial.print('\t');
		Serial.print(f.blue);
		Serial.println('\t');*/
		Serial.println(TCS.getCurrentColor().getRGB().toString());
	}
	if (Serial.available())
	{
		char C = Serial.read();
		if (C == 'B')
		{
			Serial.println("Calib deep black");
			TCS.calibDeepBlack();
			Serial.println("OK");
		}
		if (C == 'W')
		{
			Serial.println("Calib pure white");
			TCS.calibPureWhite();
			Serial.println("OK");
		}
	}


}//*/

/*
#define S0 PA1
#define S1 PA2
#define S2 PA4
#define S3 PA5
#define sensorOut PA3
int frequency = 0;
void setup() {
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(sensorOut, INPUT);


	digitalWrite(S0, HIGH);
	digitalWrite(S1, LOW);

	Serial.begin(115200);
}
void loop() {

	digitalWrite(S2, LOW);
	digitalWrite(S3, LOW);

	frequency = pulseIn(sensorOut, LOW);

	Serial.print("R= ");
	Serial.print(frequency);
	Serial.print("  ");
	delay(100);

	digitalWrite(S2, HIGH);
	digitalWrite(S3, HIGH);

	frequency = pulseIn(sensorOut, LOW);

	Serial.print("G= ");
	Serial.print(frequency);
	Serial.print("  ");
	delay(100);

	digitalWrite(S2, LOW);
	digitalWrite(S3, HIGH);

	frequency = pulseIn(sensorOut, LOW);

	Serial.print("B= ");
	Serial.print(frequency);
	Serial.println("  ");
	delay(100);
}
*/