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
	float modular(float x, float y)
	{
		if (y == 0) return 0;
		if (abs(x) < abs(y))
			return x;
		return ((int(x) / int(y))) + (x - float(int(x)));
	}
};

extern advancedMath aMath;

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
};

class HSL
{
private:
public:
	float hue, saturation, lightness;
	HSL(void) {}
	HSL(float _hue, float _saturation, float _lightness)
	{
		this->hue = constrain(_hue, 0, 359);
		this->saturation = constrain(_saturation, 0, 100);
		this->lightness = constrain(_lightness, 0, 100);
	}
	String toString()
	{
		return "HSL(" + String(hue, 0) + "," + String(saturation, 0) + "," + String(lightness, 0) + ")";
	}
};

class Colors
{
private:
	RGB _RGB;
	HSV _HSV;
	HSL _HSL;
public:
	Colors() {}
	Colors(RGB _rgb)
	{
		setColor(_rgb);
	}
	Colors(HSV _hsv)
	{
		setColor(_hsv);
	}
	Colors(HSL _hsl)
	{
		setColor(_hsl);
	}
	void setColor(RGB _rgb)
	{
		this->_RGB = _rgb;
		this->_HSV = toHSV(_rgb);
		this->_HSL = toHSL(_rgb);
	}
	void setColor(HSV _hsv)
	{
		this->_HSV = _hsv;
		this->_RGB = toRGB(_hsv);
		this->_HSL = toHSL(_hsv);
	}
	void setColor(HSL _hsl)
	{
		this->_HSL = _hsl;
		this->_RGB = toRGB(_hsl);
		this->_HSV = toHSV(_hsl);
	}

	RGB getRGB(void)
	{
		return _RGB;
	}
	HSV getHSV(void)
	{
		return _HSV;
	}
	HSL getHSL(void)
	{
		return _HSL;
	}
	HSV toHSV(RGB _rgb)
	{
		HSV _out(0, 0, 0);
		_rgb.red = constrain(_rgb.red, 0, 255);
		_rgb.green = constrain(_rgb.green, 0, 255);
		_rgb.blue = constrain(_rgb.blue, 0, 255);

		_rgb.red /= 255.0;
		_rgb.green /= 255.0;
		_rgb.blue /= 255.0;

		float M = max(_rgb.red, max(_rgb.green, _rgb.blue));
		float m = min(_rgb.red, min(_rgb.green, _rgb.blue));

		float C = M - m;

		if (C == 0)
			_out.hue = 0;
		else if (M == _rgb.red)
			_out.hue = aMath.modular(((_rgb.green - _rgb.blue) / C), 6);
		else if (M == _rgb.green)
			_out.hue = (_rgb.blue - _rgb.red) / C + 2;
		else
			_out.hue = (_rgb.red - _rgb.green) / C + 4;

		_out.hue *= 60.0;

		if (_out.hue < 0)
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
	HSV toHSV(HSL _hsl)
	{
		return toHSV(toRGB(_hsl));
	}
	HSL toHSL(HSV _hsv)
	{
		return toHSL(toRGB(_hsv));
	}
	HSL toHSL(RGB _rgb)
	{
		HSL _out(0, 0, 0);
		_rgb.red = constrain(_rgb.red, 0, 255);
		_rgb.green = constrain(_rgb.green, 0, 255);
		_rgb.blue = constrain(_rgb.blue, 0, 255);

		_rgb.red /= 255.0;
		_rgb.green /= 255.0;
		_rgb.blue /= 255.0;

		float M = max(_rgb.red, max(_rgb.green, _rgb.blue));
		float m = min(_rgb.red, min(_rgb.green, _rgb.blue));
		float d = M - m;

		if (d == 0) _out.hue = 0;
		else if (M == _rgb.red) _out.hue = aMath.modular(((_rgb.green - _rgb.blue) / d), 6);
		else if (M == _rgb.green) _out.hue = (_rgb.blue - _rgb.red) / d + 2;
		else _out.hue = (_rgb.red - _rgb.green) / d + 4;

		_out.hue *= 60;
		if (_out.hue < 0) _out.hue += 360;
		_out.lightness = (M + m) / 2;
		if (d == 0)
			_out.saturation = 0;
		else
			_out.saturation = d / (1 - abs(2 * _out.lightness - 1));
		_out.saturation *= 100;
		_out.lightness *= 100;
		return _out;
	}
	RGB toRGB(HSV _hsv)
	{
		RGB _out(0, 0, 0);
		_hsv.hue = constrain(_hsv.hue, 0, 359);
		_hsv.saturation = constrain(_hsv.saturation, 0, 100);
		_hsv.value = constrain(_hsv.value, 0, 100);

		_hsv.saturation /= 100;
		_hsv.value /= 100;

		float C = _hsv.value * _hsv.saturation;
		float hh = _hsv.hue / 60;


		float X = C * (1 - abs(aMath.modular(hh, 2.0) - 1.0));

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

		float m = _hsv.value - C;

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
	RGB toRGB(HSL _hsl)
	{
		RGB _out(0, 0, 0);
		_hsl.hue = constrain(_hsl.hue, 0, 359);
		_hsl.saturation = constrain(_hsl.saturation, 0, 100);
		_hsl.lightness = constrain(_hsl.lightness, 0, 100);

		_hsl.saturation /= 100;
		_hsl.lightness /= 100;

		float C = C = (1 - abs(2 * _hsl.lightness - 1))*_hsl.saturation;
		float hh = _hsl.hue / 60;
		float X = C * (1 - abs(aMath.modular(hh, 2) - 1));

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
		float m = _hsl.lightness - C / 2;
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

	boolean operator == (Colors & obj)
	{
		return this->_RGB.red == obj._RGB.red
			&& this->_RGB.green == obj._RGB.green
			&& this->_RGB.blue == obj._RGB.blue;
	}

	float matches(Colors _expect, boolean _withSaturation = true)
	{
		float percentMatched = 0;
		/*
		//RGB matching
		float diffRed = abs(float(this->getRGB().red - _expect.getRGB().red));
		float diffGreen = abs(this->getRGB().green - _expect.getRGB().green);
		float diffBlue = abs(this->getRGB().blue - _expect.getRGB().blue);

		float pctDiffRed = diffRed / 255;
		float pctDiffGreen = diffGreen / 255;
		float pctDiffBlue = diffBlue / 255;

		percentMatched = (pctDiffRed + pctDiffGreen + pctDiffBlue) / 3 * 100;
		*/
		
		return percentMatched;
	}
	boolean matches(const Colors _expect, float _percent, boolean _withSaturation = true);
};

#endif

