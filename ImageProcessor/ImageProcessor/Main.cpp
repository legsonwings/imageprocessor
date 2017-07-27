#include"Bitmap.h"
using namespace std;

int main()
{
	string filename = "image.bmp";
	Bitmap bitmap(filename);
	string fn = "img.bmp";
	bitmap.write(fn);
	bitmap.convertToGray();
	bitmap.write("grey.bmp");
	bitmap.threshold(105);
	bitmap.write("thresh.bmp");
}