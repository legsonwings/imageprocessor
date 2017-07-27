#pragma once
#include<string>
typedef unsigned char BYTE;

struct PIXEL
{
	BYTE R;
	BYTE G;
	BYTE B;
	PIXEL() {}
	PIXEL(BYTE val)
	{
		B = val;
		G = val;
		R = val;
	}
};

class Bitmap
{
	PIXEL **bmpData;
	BYTE bmpHeader[54];
	int height, width;
	void cleanData();
	unsigned long int nDataBytes;
public:
	Bitmap();
	Bitmap(std::string filename);
	~Bitmap();

	void read(std::string filename);
	void write(std::string filename);
	void convertToGray();
	void threshold(BYTE thresholdValue);
};
