// Colors.h

#ifndef _COLORS_h
#define _COLORS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class advancedMath
{
public:
	/*float modular(float x, float y)
	{
		if (y == 0) return 0;
		if (abs(x) < abs(y))
			return x;
		return ((int(x) / int(y))) + (x - float(int(x)));
	}*/
	float modular(float x, float y)
	{
		return x - float(int(x)/int(y)) * y;
	}
};

extern advancedMath aMath;

class HSV;

class RGB {
private:
public:
	float red, green, blue;
	RGB() {}
	RGB(float _red, float _green, float _blue)
	{
		this->red = constrain(_red, 0, 255);
		this->green = constrain(_green, 0, 255);
		this->blue = constrain(_blue, 0, 255);
	}
	String toString()
	{
		return "RGB(" + String(red, 0) + "," + String(green, 0) + "," + String(blue, 0) + ")";
	}
	HSV toHSV();

};

class HSV {
private:
public:
	float hue, saturation, value;
	HSV(void) {}
	HSV(float _hue, float _saturation, float _value)
	{
		this->hue = constrain(_hue, 0, 359);
		this->saturation = constrain(_saturation, 0, 100);
		this->value = constrain(_value, 0, 100);
	}
	String toString()
	{
		return "HSV(" + String(hue, 0) + "," + String(saturation, 0) + "," + String(value, 0) + ")";
	}
	RGB toRGB(void)
	{
		RGB _out;
		hue = constrain(hue, 0, 359);
		saturation = constrain(saturation, 0, 100);
		value = constrain(value, 0, 100);

		saturation /= 100;
		value /= 100;

		float C = value * saturation;
		float hh = hue / 60;


		float X = C * (1 - abs(aMath.modular(hh, 2.0) - 1.0));
		_out.red = 0;
		_out.green = 0;
		_out.blue = 0;

		if (hh >= 0 && hh < 1)
		{
			_out.red = C;
			_out.green = X;
		}
		else if (hh >= 1 && hh < 2)
		{
			_out.red = X;
			_out.green = C;
		}
		else if (hh >= 2 && hh < 3)
		{
			_out.green = C;
			_out.blue = X;
		}
		else if (hh >= 3 && hh < 4)
		{
			_out.green = X;
			_out.blue = C;
		}
		else if (hh >= 4 && hh < 5)
		{
			_out.red = X;
			_out.blue = C;
		}
		else
		{
			_out.red = C;
			_out.blue = X;
		}

		float m = value - C;

		_out.red += m;
		_out.green += m;
		_out.blue += m;

		_out.red *= 255.0;
		_out.green *= 255.0;
		_out.blue *= 255.0;

		_out.red = round(_out.red);
		_out.green = round(_out.green);
		_out.blue = round(_out.blue);

		return _out;
	}
	friend HSV RGB::toHSV();
};

HSV RGB::toHSV()
{
	HSV _out;
	red = constrain(red, 0, 255);
	green = constrain(green, 0, 255);
	blue = constrain(blue, 0, 255);

	red /= 255.0;
	green /= 255.0;
	blue /= 255.0;

	float M = max(red, max(green, blue));
	float m = min(red, min(green, blue));

	float C = M - m;

	if (C == 0) 
		_out.hue = 0;
	else if (M == red) 
		_out.hue = aMath.modular(((green - blue) / C) , 6);
	else if (M == green) 
		_out.hue = (blue - red) / C + 2;
	else 
		_out.hue = (red - green) / C + 4;

	_out.hue *= 60.0;

	if (_out.hue<0)
		_out.hue += 360;
	_out.value = M;

	if (_out.value == 0)
		_out.saturation = 0;
	else
		_out.saturation = C / _out.value;

	_out.saturation *= 100;
	_out.value *= 100;

	return _out;
}

class Colors
{
private:
	RGB _RGB;
	HSV _HSV;
public:

	Colors(RGB _RGB)
	{
		SetColor(_RGB);
	}
	Colors(HSV _HSV)
	{
		SetColor(_HSV);
	}
	void SetColor(RGB _RGB)
	{
		this->_RGB = _RGB;
	}
	void SetColor(HSV _HSV)
	{
		this->_HSV = _HSV;
	}

	RGB GetRGB(void)
	{
		return _RGB;
	}
	HSV GetHSV(void)
	{
		return _HSV;
	}

	float Matches(const Colors _expect, boolean _withSaturation = true);
	boolean Matches(const Colors _expect, float _percent, boolean _withSaturation = true);
};

#endif

