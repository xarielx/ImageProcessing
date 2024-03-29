#include "stdafx.h"
#include "Image.h"
#include "Pixel.h"


#include <fstream>

#include <vector>
#include <iosfwd>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <chrono> 

using namespace std;

int size1 = 0;
int size2 = 0;
char * compareFiles(string image1);
//bool compare(string lFilePath, string rFilePath);
void QuickCompare(vector<Image> &one, vector<Image> &two);
void slowCompare(vector<Image> &one, vector<Image> &two);

int main()
{
	
	


	Image image;

	vector<Image> outvec;
	//image.writeImage("car.tga", "circles.tga", "pattern1.tga", "text.tga"); 

		image.readImage("EXAMPLE_part1.tga", outvec);
		image.readImage("EXAMPLE_part2.tga", outvec);
		image.readImage("EXAMPLE_part3.tga", outvec);
		image.readImage("EXAMPLE_part4.tga", outvec);
		image.readImage("EXAMPLE_part5.tga", outvec);
		image.readImage("EXAMPLE_part6.tga", outvec);
		image.readImage("EXAMPLE_part7.tga", outvec);
		image.readImage("EXAMPLE_part8_G.tga", outvec);
		image.readImage("EXAMPLE_part8_R.tga", outvec);
		image.readImage("EXAMPLE_part8_B.tga", outvec);
		image.readImage("EXAMPLE_part9.tga", outvec);
		image.readImage("EXAMPLE_part10.tga", outvec);

	image.multiplyImages("layer1.tga", "pattern1.tga", "part1.tga");
	image.subtractBlending("car.tga", "layer2.tga", "part2.tga");
	image.ScreenBlendingMode("pattern2.tga", "layer1.tga", "part3.tga");
	image.PartFour();
	image.overlayImages("layer1.tga", "pattern1.tga");
	image.addToChannel("car.tga", "Part6.tga", 'G', 200);
	image.FlipImage("text2.tga", "part10.tga");
	image.writeChannel("car.tga", "part8", 'R');
	image.writeChannel("car.tga", "part8", 'G');
	image.writeChannel("car.tga", "part8", 'B');
	image.scale("car.tga", 'R', 4, 'B', 0, "part7.tga");
	image.combineLayers("layer_red.tga", "layer_green.tga", "layer_blue.tga", "part9.tga");

	vector<Image> outvec2;
	image.readImage("part1.tga", outvec2);
	image.readImage("part2.tga", outvec2);
	image.readImage("part3.tga", outvec2);
	image.readImage("part4.tga", outvec2);
	image.readImage("part5.tga", outvec2);
	image.readImage("part6.tga", outvec2);
	image.readImage("part7.tga", outvec2);
	image.readImage("part8_G.tga", outvec2);
	image.readImage("part8_R.tga", outvec2);
	image.readImage("part8_B.tga", outvec2);
	image.readImage("part9.tga", outvec2);
	image.readImage("part10.tga", outvec2);

//	compare("Input\\EXAMPLE_part3.tga", "Output\\part3.tga");

	QuickCompare(outvec, outvec2);
	slowCompare(outvec, outvec2);
	

    return 0;
}

void slowCompare(vector<Image> &one, vector<Image> &two)
{
	int score = 0;
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
	bool failed = false;
	
	for (int i = 0; i < one.size(); i++)
	{
		if (one[i].header.idLength == two[i].header.idLength)
		{
			failed = (true);
		}
		if (one[i].header.colourMapType == two[i].header.colourMapType)
		{
			failed = (true);
		}
		if (one[i].header.dataTypeCode == two[i].header.dataTypeCode)
		{
			failed = (true);
		}
		if (one[i].header.colourMapOrigin == two[i].header.colourMapOrigin)
		{
			failed = (true);
		}
		if (one[i].header.colourMapLength == two[i].header.colourMapLength)
		{
			failed = (true);
		}
		if (one[i].header.colourMapDepth == two[i].header.colourMapDepth)
		{
			failed = (true);
		}
		if (one[i].header.xOrigin == two[i].header.xOrigin)
		{
			failed = (true);
		}
		if (one[i].header.yOrigin == two[i].header.yOrigin)
		{
			failed = (true);
		}
		if (one[i].header.width == two[i].header.width)
		{
			failed = (true);
		}
		if (one[i].header.height == two[i].header.height)
		{
			failed = (true);
		}
		if (one[i].header.bitsPerPixel == two[i].header.bitsPerPixel)
		{
			failed = (true);
		}
		if (one[i].header.imageDescriptor == two[i].header.imageDescriptor)
		{
			failed = (true);
		}
		if (one[i].pixelV.size() != two[i].pixelV.size())
		{
			failed = (true);
		}
		
		for (size_t j = 0; j < one[i].pixelV.size(); j++) {
			if (one[i].pixelV[j].B != two[i].pixelV[j].B)
			{
				failed = (false);
				break;
			}
			if (one[i].pixelV[j].G != two[i].pixelV[j].G)
			{
				failed = (false);
				break;
			}
			if (one[i].pixelV[j].R != two[i].pixelV[j].R)
			{
				failed = (false);
				break;
			}
		}


		if (failed == false)
		{
			cout << "Images " << one[i].ImageName << " and " << two[i].ImageName << " are different!!!!" << endl;
		}
		else
		{
				score += 20;
			
			cout << "Comparing Image to example: " << two[i].ImageName << " was succesfull +" << score << " points" << endl;
		}
	}
	cout << "Total score: " << score << endl;
	// Recording end time
	auto finish = std::chrono::high_resolution_clock::now();

	//We create a duration 
	std::chrono::duration<double> elapsed = finish - start;

	std::cout << "Loading files manually time: " << elapsed.count() << " s\n";

}

char* compareFiles(string image1)
{
	ifstream file;
	size_t size = 0; // here

	file.open("Input\\"+image1, ios::in | ios::binary | ios::ate);
	if (!file)
	{
		file.open("Output\\" + image1, ios::in | ios::binary | ios::ate);
	}
	char* oData = 0;

	file.seekg(0, ios::end); // set the pointer to the end
	size = file.tellg(); // get the length of the file
	//cout << "Size of file 1: " << size << endl;
	file.seekg(0, ios::beg); // set the pointer to the beginning

	oData = new char[size + 1]; //  for the '\0'
	file.read(oData, size);
	oData[size] = '\0'; // set '\0' 

	
	return oData;
}


void QuickCompare(vector<Image> &one, vector<Image> &two)
{
	int score = 0;
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();

	// Portion of code to be timed
	
	int partCount = 0;
	int part = 9;
	for (size_t i = 0; i < one.size(); i++)
	{
		char * t = compareFiles(one[i].ImageName);
		char * r = compareFiles(two[i].ImageName);
		bool compareBytes = true;
		if (size1 == size2) {
			for (unsigned int i = 0; i < size1; i++)
			{
				if (t[i] != r[i])
				{
					cout << "Files are not the same!!" << endl;
					cout << i << endl;
					compareBytes = false;
					break;
				}

			}
		}
		else { compareBytes = false; }
		
			if (compareBytes == true)
			{
	
					partCount++;
				score += 20;
				cout << "Part " << partCount << " was succesful!" << " +20 points" << endl;
			}
	}

	
	cout << "Total score: " << score << endl;


		// Record end time
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;

		std::cout << "Quick Binary Load and compare time: " << elapsed.count() << " s\n";
	
	
}