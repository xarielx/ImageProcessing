#pragma once
#include "Pixel.h"
#include "Header.h"
#include "stdafx.h"
#include <fstream>

#include <vector>
#include <iosfwd>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <conio.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <Windows.h>


using namespace std;


struct FloatPixel
{
	float blue, green, red;
};

class Image
{
public:
	string ImageName;
	//Pixel * pixels;
	vector<Pixel> pixelV;
	Header header;
	char * ImageData;
	bool rotate = FALSE;

	void writeChannel(string imageName, string part, char chanel);
	void overlayImages(string imageA, string imageB);
	Image multiplyBlend(string image1, string image2, string part);
	void readImage(string imageName, vector<Image> &inImages);
	Image readImageOne(string imageName);
	void writeCopyOfImage(Image image);
	void FlipImage(std::string imageName, string part);
	void writeImage(string one, string two, string three, string four);
	void multiplyImages(string image1, string image2, string part);
	void forwardWrite(ofstream &dst, Image image);
	void reverseWrite(ofstream &dst, Image image);
	void writeHeader(ofstream &dst, Image image);
	void subtractBlending(string image1, string image2, string part);
	void ScreenBlendingMode(string image1, string image2, string part);
	void PartFour();
	void addToChannel(string imageName, string part, char chanel, int amount);
	void scale(string ImageName, char chanel, int amount, char chanel2, int amount2, string part);
	void combineLayers(string image1, string image2, string image3, string part);
};