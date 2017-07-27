#include"Bitmap.h"
#include<iostream>
#include<fstream>

Bitmap::Bitmap()
{
	bmpData = nullptr;
}

Bitmap::Bitmap(std::string filename)
{
	read(filename);
}

Bitmap::~Bitmap()
{
	if (bmpData!= nullptr)
	{
		cleanData();
	}
}

void Bitmap::read(std::string filename)
{	
	std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
	if (!in.good())
	{
		std::cout << "Unable to open the file.\n";
		return;
	}
	cleanData();

	in.read(reinterpret_cast<char *>(bmpHeader), sizeof(bmpHeader));
	width = *(reinterpret_cast<int *>(&bmpHeader[18]));
	height = *(reinterpret_cast<int *>(&bmpHeader[22]));

	nDataBytes = width*height * 3;
	BYTE *tempBuf = new BYTE[nDataBytes];

	bmpData = new PIXEL*[height];
	for (size_t row = 0; row < height; row++)
		bmpData[row] = new PIXEL[width];

	in.read(reinterpret_cast<char *>(tempBuf), nDataBytes);
	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			PIXEL pixel;
			pixel.B = tempBuf[row* width * 3 + col * 3 + 0];
			pixel.G = tempBuf[row* width * 3 + col * 3 + 1];
			pixel.R = tempBuf[row* width * 3 + col * 3 + 2];
			bmpData[row][col] = pixel;
		}
	}
	delete[] tempBuf;
}

void Bitmap::write(std::string filename)
{
	std::ofstream out(filename, std::ofstream::out | std::ofstream::binary);
	
	BYTE *writeBuf = new BYTE[nDataBytes];
	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			PIXEL pixel = bmpData[row][col];
			writeBuf[row*width * 3 + col * 3 + 0] = pixel.B;
			writeBuf[row*width * 3 + col * 3 + 1] = pixel.G;
			writeBuf[row*width * 3 + col * 3 + 2] = pixel.R;
		}
	}

	out.write(reinterpret_cast<const char *>(bmpHeader), sizeof(bmpHeader));
	out.write(reinterpret_cast<const char *>(writeBuf), nDataBytes);

	/*BYTE *img = new BYTE[nDataBytes + 54];
	memcpy(img, bmpHeader, 54);
	memcpy(img + 54, writeBuf , nDataBytes);
	out.write(reinterpret_cast<const char *>(img), nDataBytes+54);
	*/
	delete[] writeBuf;
}
void Bitmap::convertToGray()
{
	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{

			PIXEL p = bmpData[row][col];
			BYTE greyVal = ((int)p.B + (int)p.B + (int)p.R) / 3;
			bmpData[row][col] = PIXEL(greyVal);
		}
	}
}

void Bitmap::threshold(BYTE threshold)
{
	for (size_t row = 0; row < height; row++)
	{
		for (size_t col = 0; col < width; col++)
		{
			PIXEL p = bmpData[row][col];
			if (static_cast<int>(p.B) < static_cast<int>(threshold))
				p = PIXEL(0);
			else
				p = PIXEL(255);
			bmpData[row][col] = p;
		}
	}
}
void Bitmap::cleanData()
{
	for (size_t row = 0; row < height; row++)
		delete[] bmpData[row]; 
	delete [] bmpData;
	bmpData = nullptr;
}

