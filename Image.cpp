#include "stdafx.h"
#include "Image.h"

void Image::readImage(string filename, vector<Image> &inImages)
{

	Image tmp;
	tmp.ImageName = filename;
	ifstream file;

	file.open("Input\\" + filename, ios::in | ios::binary);


	//file.open("Output\\" + filename, ios::in | ios::binary);

	if (!file)
	{
		file.open("Output\\" + filename, ios::in | ios::binary);
		if (!file)
		{
			cout << "File not found!" << endl;
			exit(1);
		}
	}
	file.read((char *)&tmp.header.idLength, sizeof(char));
	file.read((char *)&tmp.header.colourMapType, sizeof(char));
	file.read((char *)&tmp.header.dataTypeCode, sizeof(char));

	file.read((char *)&tmp.header.colourMapOrigin, sizeof(short));
	file.read((char *)&tmp.header.colourMapLength, sizeof(short));
	file.read((char *)&tmp.header.colourMapDepth, sizeof(char));

	file.read((char *)&tmp.header.xOrigin, sizeof(short));
	file.read((char *)&tmp.header.yOrigin, sizeof(short));

	file.read((char *)&tmp.header.width, sizeof(short));
	file.read((char *)&tmp.header.height, sizeof(short));

	file.read((char *)&tmp.header.bitsPerPixel, sizeof(char));
	file.read((char *)&tmp.header.imageDescriptor, sizeof(char));

	tmp.ImageData = new char[3];

	unsigned int pixelcount = tmp.header.height * tmp.header.width; // Number Of Pixels In The Image
	unsigned int currentpixel = 0;            // Current Pixel We Are Reading From Data
	unsigned int currentbyte = 0;            // Current Byte We Are Writing Into Imagedata
	unsigned int bitsPerPixel = 3;
	//tmp.pixels = new Pixel[tmp.header.height * tmp.header.width];
	do
	{
		Pixel filler;
		file.read(tmp.ImageData, bitsPerPixel);
		//tmp.pixels[currentpixel].B = tmp.ImageData[0];
		//tmp.pixels[currentpixel].G = tmp.ImageData[1];
		//tmp.pixels[currentpixel].R = tmp.ImageData[2];
		filler.B = tmp.ImageData[0];
		filler.G = tmp.ImageData[1];
		filler.R = tmp.ImageData[2];
		tmp.pixelV.push_back(filler);

		currentbyte += 3;   // Increment The Byte Counter
		currentpixel++;             // Increment The Pixel Counter

	} while (currentpixel < pixelcount);

	file.close();
	inImages.push_back(tmp);

}
Image Image::readImageOne(string filename)
{
	Image tmp;
	tmp.ImageName = filename;
	ifstream file;

	file.open("Input\\" + filename, ios::in | ios::binary);


	//file.open("Output\\" + filename, ios::in | ios::binary);

	if (!file)
	{
		file.open("Output\\" + filename, ios::in | ios::binary);
		if (!file)
		{
			cout << "File not found!" << endl;
			exit(1);
		}
	}
	file.read((char *)&tmp.header.idLength, sizeof(char));
	file.read((char *)&tmp.header.colourMapType, sizeof(char));
	file.read((char *)&tmp.header.dataTypeCode, sizeof(char));

	file.read((char *)&tmp.header.colourMapOrigin, sizeof(short));
	file.read((char *)&tmp.header.colourMapLength, sizeof(short));
	file.read((char *)&tmp.header.colourMapDepth, sizeof(char));

	file.read((char *)&tmp.header.xOrigin, sizeof(short));
	file.read((char *)&tmp.header.yOrigin, sizeof(short));

	file.read((char *)&tmp.header.width, sizeof(short));
	file.read((char *)&tmp.header.height, sizeof(short));

	file.read((char *)&tmp.header.bitsPerPixel, sizeof(char));
	file.read((char *)&tmp.header.imageDescriptor, sizeof(char));

	tmp.ImageData = new char[3];

	unsigned int pixelcount = tmp.header.height * tmp.header.width; // Number Of Pixels In The Image
	unsigned int currentpixel = 0;            // Current Pixel We Are Reading From Data
	unsigned int currentbyte = 0;            // Current Byte We Are Writing Into Imagedata
	unsigned int bitsPerPixel = 3;
	//tmp.pixels = new Pixel[tmp.header.height * tmp.header.width];
	do
	{
		Pixel filler;
		file.read(tmp.ImageData, bitsPerPixel);
		//tmp.pixels[currentpixel].B = tmp.ImageData[0];
		//tmp.pixels[currentpixel].G = tmp.ImageData[1];
		//tmp.pixels[currentpixel].R = tmp.ImageData[2];
		filler.B = tmp.ImageData[0];
		filler.G = tmp.ImageData[1];
		filler.R = tmp.ImageData[2];
		tmp.pixelV.push_back(filler);

		currentbyte += 3;   // Increment The Byte Counter
		currentpixel++;             // Increment The Pixel Counter

	} while (currentpixel < pixelcount);

	file.close();
	return tmp;

}





void Image::reverseWrite(ofstream &dst, Image image)
{

	//vector<Pixel>::reverse_iterator it = image.pixelV.rbegin();
	for (vector<Pixel>::reverse_iterator it = image.pixelV.rbegin(); it != image.pixelV.rend(); ++it)
	{
		Pixel temp = *it;
		dst.write((const char*)&temp.B, 1);
		dst.write((const char*)&temp.G, 1);
		dst.write((const char*)&temp.R, 1);
	}

	/*for (int i = image.header.width * image.header.height; i >= 0; i--)
	{
	dst.put(image.pixels[i].B);
	dst.put(image.pixels[i].G);
	dst.put(image.pixels[i].R);
	}*/
}

void Image::forwardWrite(ofstream &dst, Image image)
{
	for (auto & it : image.pixelV)
	{
		dst.write((const char*)&it.B, 1);
		dst.write((const char*)&it.G, 1);
		dst.write((const char*)&it.R, 1);
	}
}
void Image::writeHeader(ofstream &dst, Image image)
{
	dst.write((const char*)&image.header.idLength, sizeof(image.header.idLength));
	dst.write((const char*)&image.header.colourMapType, sizeof(image.header.colourMapType));
	dst.write((const char*)&image.header.dataTypeCode, sizeof(image.header.dataTypeCode));
	dst.write((const char*)&image.header.colourMapOrigin, sizeof(image.header.colourMapOrigin));
	dst.write((const char*)&image.header.colourMapLength, sizeof(image.header.colourMapLength));
	dst.write((const char*)&image.header.colourMapDepth, sizeof(image.header.colourMapDepth));
	dst.write((const char*)&image.header.xOrigin, sizeof(image.header.xOrigin));
	dst.write((const char*)&image.header.yOrigin, sizeof(image.header.yOrigin));
	dst.write((const char*)&image.header.width, sizeof(image.header.width));
	dst.write((const char*)&image.header.height, sizeof(image.header.height));
	dst.write((const char*)&image.header.bitsPerPixel, sizeof(image.header.bitsPerPixel));
	dst.write((const char*)&image.header.imageDescriptor, sizeof(image.header.imageDescriptor));
}

void Image::writeCopyOfImage(Image image)
{

	//system("mkdir Output");
	//cout << &image.headr.idLength << endl;

	std::ofstream  dst("Output\\" + image.ImageName, std::ios::binary);
	writeHeader(dst, image);
	if (image.rotate == false)
	{
		forwardWrite(dst, image);
	}
	else
	{
		reverseWrite(dst, image);
	}

}

//Rotate 180 Degrees
void Image::FlipImage(std::string imageName, string part)
{
	Image image;
	vector<Image> temp;
	bool n = TRUE;
	image.readImage(imageName, temp);
	image = temp[0];
	image.ImageName = part;

	image.rotate = TRUE;
	writeCopyOfImage(image);

}

Header defaultHeader()
{
	Header tmp;
	tmp.idLength = 0;
	tmp.colourMapType = 0;
	tmp.dataTypeCode = 2;
	tmp.colourMapOrigin = 0;
	tmp.colourMapLength = 0;
	tmp.colourMapDepth = 0;
	tmp.xOrigin = 0;
	tmp.yOrigin = 0;
	tmp.width = 512;
	tmp.height = 512;
	tmp.bitsPerPixel = 24;
	tmp.imageDescriptor = 0;
	return tmp;
}

//Part1
void Image::multiplyImages(string image1, string image2, string part)
{


	//reading both images
	vector<Image> Layers;
	bool n = TRUE;
	readImage(image1, Layers);
	readImage(image2, Layers);
	Image image;
	image.ImageName = part;
	image.header = defaultHeader();
	//assuming they are the same width and height
	int imageSize = Layers[0].header.height * Layers[0].header.width;
	vector<FloatPixel> temp(imageSize);

	for (int i = 0; i < imageSize; i++)
	{
		temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255) * ((float)(int)(Layers[1].pixelV[i].B) / 255));
		temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255) * ((float)(int)(Layers[1].pixelV[i].G) / 255));
		temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255) * ((float)(int)(Layers[1].pixelV[i].R) / 255));
	}

	image.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		image.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		image.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		image.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		j++;
	}

	writeCopyOfImage(image);

}
Image Image::multiplyBlend(string image1, string image2, string part)
{
	//reading both images
	vector<Image> Layers;
	readImage(image1, Layers);
	readImage(image2, Layers);
	Image image;
	image.ImageName = part;
	image.header = defaultHeader();
	//assuming they are the same width and height
	int imageSize = Layers[0].header.height * Layers[0].header.width;
	vector<FloatPixel> temp(imageSize);

	for (int i = 0; i < imageSize; i++)
	{
		temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255) * ((float)(int)(Layers[1].pixelV[i].B) / 255));
		temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255) * ((float)(int)(Layers[1].pixelV[i].G) / 255));
		temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255) * ((float)(int)(Layers[1].pixelV[i].R) / 255));
	}

	image.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		image.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		image.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		image.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		j++;
	}

	return image;
}


void Image::subtractBlending(string image1, string image2, string part)
{
	Image result;
	result.ImageName = part;
	vector<Image> Layers;
	readImage(image1, Layers);
	readImage(image2, Layers);
	result.header = defaultHeader();
	int imageSize = Layers[0].header.height * Layers[0].header.width;

	vector<FloatPixel> temp(imageSize);
	int min, max;
	min = 0;
	max = 255;
	for (int i = 0; i < imageSize; i++)
	{
		temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255) - ((float)(int)(Layers[1].pixelV[i].B) / 255));
		temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255) - ((float)(int)(Layers[1].pixelV[i].G) / 255));
		temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255) - ((float)(int)(Layers[1].pixelV[i].R) / 255));
	}
	result.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		if (((it.blue * 255) + 0.5f) < min)
		{
			result.pixelV[j].B = (unsigned char)0;
		}
		else if (((it.blue * 255) + 0.5f) > max)
		{
			result.pixelV[j].B = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		}
		if (((it.green * 255) + 0.5f) < min)
		{
			result.pixelV[j].G = (unsigned char)0;
		}
		else if (((it.green * 255) + 0.5f) > max)
		{
			result.pixelV[j].G = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		}
		if (((it.red * 255) + 0.5f) < min)
		{
			result.pixelV[j].R = (unsigned char)0;
		}
		else if (((it.red * 255) + 0.5f) > max)
		{
			result.pixelV[j].R = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		}
		j++;
	}

	writeCopyOfImage(result);
}

void Image::ScreenBlendingMode(string image1, string image2, string part)
{
	//C=1-(1-A)*(1-B)
	vector<Image> Layers;
	readImage(image1, Layers);
	readImage(image2, Layers);
	Image image;
	image.ImageName = part;
	image.header = defaultHeader();
	//assuming they are the same width and height
	int imageSize = Layers[0].header.height * Layers[0].header.width;
	vector<FloatPixel> temp(imageSize);

	for (int i = 0; i < imageSize; i++)
	{
		temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255) * ((float)(int)(Layers[1].pixelV[i].B) / 255));
		temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255) * ((float)(int)(Layers[1].pixelV[i].G) / 255));
		temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255) * ((float)(int)(Layers[1].pixelV[i].R) / 255));
	}

	image.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		image.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		image.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		image.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		j++;
	}

	//writeCopyOfImage(image);
	Image result = image;

	result.ImageName = part;

	vector<Image> Layers1;
	readImage("text.tga", Layers1);
	Layers1.push_back(image);
	//readImage("temp.tga", Layers1);
	result.header = defaultHeader();
	int imageSize1 = Layers1[0].header.height * Layers1[0].header.width;

	vector<FloatPixel> temp1(imageSize1);

	for (int i = 0; i < imageSize1; i++)
	{
		temp1[i].blue = 1 - ((1 - ((float)(int)(Layers1[0].pixelV[i].B) / 255))  * (1 - ((float)(int)(Layers1[1].pixelV[i].B) / 255)));
		temp1[i].green = 1 - ((1 - ((float)(int)(Layers1[0].pixelV[i].G) / 255)) * (1 - ((float)(int)(Layers1[1].pixelV[i].G) / 255)));
		temp1[i].red = 1 - ((1 - ((float)(int)(Layers1[0].pixelV[i].R) / 255)) * (1 - ((float)(int)(Layers1[1].pixelV[i].R) / 255)));
	}
	result.pixelV.resize(imageSize1);
	int j1 = 0;
	for (auto & it : temp1)
	{
		result.pixelV[j1].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		result.pixelV[j1].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		result.pixelV[j1].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		j1++;
	}
	result.ImageName = "Part3.tga";
	writeCopyOfImage(result);
}

void Image::PartFour()
{
	Image PartFour;

	PartFour.multiplyImages("layer2.tga", "circles.tga", "Part4.tga");


	PartFour.subtractBlending("Part4.tga", "pattern2.tga", "Part4.tga");

	//	PartFour.subtractBlending("PartFour.tga", "pattern2.tga", "PartFour.tga");

}
void Image::overlayImages(string imageA, string imageB)

{
	Image image;
	image.header = defaultHeader();
	vector<Image> vec;
	image.readImage(imageA, vec);
	image.readImage(imageB, vec);
	image.ImageName = "Part5.tga";
	int imageSize = vec[0].header.height * vec[0].header.width;
	vector<FloatPixel> temp(imageSize);

	for (int i = 0; i < imageSize; i++)
	{
		if (((float)(int)(vec[1].pixelV[i].B) / 255) < 0.5)
		{
			temp[i].blue = 2 * (((float)(int)(vec[0].pixelV[i].B) / 255) * ((float)(int)(vec[1].pixelV[i].B) / 255));
		}
		else
		{
			temp[i].blue = 1 - (2 * ((1 - ((float)(int)(vec[0].pixelV[i].B) / 255))  * (1 - ((float)(int)(vec[1].pixelV[i].B) / 255))));
		}
		if (((float)(int)(vec[1].pixelV[i].G) / 255) < 0.5)
		{
			temp[i].green = 2 * (((float)(int)(vec[0].pixelV[i].G) / 255) * ((float)(int)(vec[1].pixelV[i].G) / 255));
		}
		else
		{
			temp[i].green = 1 - (2 * ((1 - ((float)(int)(vec[0].pixelV[i].G) / 255)) * (1 - ((float)(int)(vec[1].pixelV[i].G) / 255))));
		}
		if (((float)(int)(vec[1].pixelV[i].R) / 255) < 0.5)
		{
			temp[i].red = 2 * (((float)(int)(vec[0].pixelV[i].R) / 255) * ((float)(int)(vec[1].pixelV[i].R) / 255));
		}
		else
		{
			temp[i].red = 1 - (2 * ((1 - ((float)(int)(vec[0].pixelV[i].R) / 255)) * (1 - ((float)(int)(vec[1].pixelV[i].R) / 255))));
		}
	}

	image.pixelV.resize(imageSize);
	int j = 0;
	int min, max;
	min = 0;
	max = 255;
	for (auto & it : temp)
	{
		if (((it.blue * 255) + 0.5f) < min)
		{
			image.pixelV[j].B = (unsigned char)0;
		}
		else if (((it.blue * 255) + 0.5f) > max)
		{
			image.pixelV[j].B = (unsigned char)255;
		}
		else
		{
			image.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		}
		if (((it.green * 255) + 0.5f) < min)
		{
			image.pixelV[j].G = (unsigned char)0;
		}
		else if (((it.green * 255) + 0.5f) > max)
		{
			image.pixelV[j].G = (unsigned char)255;
		}
		else
		{
			image.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		}
		if (((it.red * 255) + 0.5f) < min)
		{
			image.pixelV[j].R = (unsigned char)0;
		}
		else if (((it.red * 255) + 0.5f) > max)
		{
			image.pixelV[j].R = (unsigned char)255;
		}
		else
		{
			image.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		}
		j++;
	}

	writeCopyOfImage(image);
}


void Image::addToChannel(string imageName, string part, char chanel, int amount)
{
	Image result;
	result.ImageName = part;
	vector<Image> Layers;
	readImage(imageName, Layers);

	result.header = defaultHeader();
	int imageSize = Layers[0].header.height * Layers[0].header.width;

	vector<FloatPixel> temp(imageSize);
	int min, max;
	min = 0;
	max = 255;
	/*for (int i = 0; i < imageSize; i++)
	{
	temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255));
	temp[i].green = (float)((int)(Layers[0].pixelV[i].G) + 200) / 255;
	temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255));
	}*/
	if (chanel == 'R' || chanel == 'r')
	{
		for (int i = 0; i < imageSize; i++)
		{
			temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255));
			temp[i].green = (((float)(int)(Layers[0].pixelV[i].B) / 255));
			temp[i].red = (float)((int)(Layers[0].pixelV[i].R) + 200) / 255;
		}
	}
	if (chanel == 'G' || chanel == 'g')
	{
		for (int i = 0; i < imageSize; i++)
		{
			temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255));
			temp[i].green = (float)((int)(Layers[0].pixelV[i].G) + 200) / 255;
			temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255));
		}
	}
	if (chanel == 'B' || chanel == 'b')
	{
		for (int i = 0; i < imageSize; i++)
		{
			temp[i].blue = (float)((int)(Layers[0].pixelV[i].B) + 200) / 255;
			temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255));
			temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255));
		}
	}


	result.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		if (((it.blue * 255) + 0.5f) < min)
		{
			result.pixelV[j].B = (unsigned char)0;
		}
		else if (((it.blue * 255) + 0.5f) > max)
		{
			result.pixelV[j].B = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		}
		if (((it.green * 255) + 0.5f) < min)
		{
			result.pixelV[j].G = (unsigned char)0;
		}
		else if (((it.green * 255) + 0.5f) > max)
		{
			result.pixelV[j].G = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		}
		if (((it.red * 255) + 0.5f) < min)
		{
			result.pixelV[j].R = (unsigned char)0;
		}
		else if (((it.red * 255) + 0.5f) > max)
		{
			result.pixelV[j].R = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		}
		j++;
	}

	writeCopyOfImage(result);

}



void Image::writeChannel(string imageName, string part, char chanel)
{
	Image image;
	vector<Image> temp;
	readImage(imageName, temp);
	image = temp[0];
	//system("mkdir Output");
	//cout << &image.headr.idLength << endl;
	string name = part.substr(0, 5);
	std::ofstream  dst("Output\\" + part + "_" + chanel + ".tga", std::ios::binary);
	writeHeader(dst, image);
	int mynum = 0;
	unsigned char r = (unsigned char)mynum;
	if (chanel == 'r' || chanel == 'R')
	{

		for (auto & it : image.pixelV)
		{
			dst.write((const char*)&it.R, 1);
			dst.write((const char*)&it.R, 1);
			dst.write((const char*)&it.R, 1);
		}
	}
	if (chanel == 'b' || chanel == 'B')
	{
		for (auto & it : image.pixelV)
		{
			dst.write((const char*)&it.B, 1);
			dst.write((const char*)&it.B, 1);
			dst.write((const char*)&it.B, 1);
		}
	}
	if (chanel == 'g' || chanel == 'G')
	{
		for (auto & it : image.pixelV)
		{
			dst.write((const char*)&it.G, 1);
			dst.write((const char*)&it.G, 1);
			dst.write((const char*)&it.G, 1);
		}
	}


}


//for modifying a chanell make all channels the same amount of the given channel
//dont convert to float when adding  pixels just add
//use write not put and 


//scaling is multiply the channel 
void Image::scale(string ImageName, char chanel1, int amount, char chanel2, int amount2, string part)
{
	Image result;
	result.ImageName = part;
	vector<Image> Layers;
	readImage("car.tga", Layers);

	result.header = defaultHeader();
	int imageSize = Layers[0].header.height * Layers[0].header.width;

	vector<FloatPixel> temp(imageSize);
	int min, max;
	min = 0;
	max = 255;
	char chanel = chanel1;
	for (int r = 0; r < 2; r++)
	{
		if (chanel == 'R' || chanel == 'r')
		{
			for (int i = 0; i < imageSize; i++)
			{
				temp[i].blue = (float)((int)(Layers[0].pixelV[i].B) * 0) / 255;
				temp[i].green = (((float)(int)(Layers[0].pixelV[i].B) / 255));
				temp[i].red = (float)((int)(Layers[0].pixelV[i].R) * 4) / 255;
			}
		}
		if (chanel == 'G' || chanel == 'g')
		{
			for (int i = 0; i < imageSize; i++)
			{
				temp[i].blue = (((float)(int)(Layers[0].pixelV[i].B) / 255));
				temp[i].green = (float)((int)(Layers[0].pixelV[i].G) + 200) / 255;
				temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255));
			}
		}
		if (chanel == 'B' || chanel == 'b')
		{
			for (int i = 0; i < imageSize; i++)
			{
				temp[i].blue = (float)((int)(Layers[0].pixelV[i].B) * 0) / 255;
				temp[i].green = (((float)(int)(Layers[0].pixelV[i].G) / 255));
				temp[i].red = (float)((int)(Layers[0].pixelV[i].R) * 4) / 255;
			}
		}
		chanel = chanel2;
	}
	result.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		if (((it.blue * 255) + 0.5f) < min)
		{
			result.pixelV[j].B = (unsigned char)0;
		}
		else if (((it.blue * 255) + 0.5f) > max)
		{
			result.pixelV[j].B = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		}
		if (((it.green * 255) + 0.5f) < min)
		{
			result.pixelV[j].G = (unsigned char)0;
		}
		else if (((it.green * 255) + 0.5f) > max)
		{
			result.pixelV[j].G = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		}
		if (((it.red * 255) + 0.5f) < min)
		{
			result.pixelV[j].R = (unsigned char)0;
		}
		else if (((it.red * 255) + 0.5f) > max)
		{
			result.pixelV[j].R = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		}
		j++;
	}

	writeCopyOfImage(result);

}

void Image::combineLayers(string image1, string image2, string image3, string part)
{
	Image result;
	result.ImageName = part;
	vector<Image> Layers;
	readImage(image1, Layers);
	readImage(image2, Layers);
	readImage(image3, Layers);
	result.header = Layers[1].header;
	int imageSize = Layers[0].header.height * Layers[0].header.width;

	vector<FloatPixel> temp(imageSize);
	int min, max;
	min = 0;
	max = 255;
	for (int i = 0; i < imageSize; i++)
	{
		temp[i].blue = (((float)(int)(Layers[2].pixelV[i].B) / 255));
		temp[i].green = (((float)(int)(Layers[1].pixelV[i].G) / 255));
		temp[i].red = (((float)(int)(Layers[0].pixelV[i].R) / 255));
	}
	result.pixelV.resize(imageSize);
	int j = 0;
	for (auto & it : temp)
	{
		if (((it.blue * 255) + 0.5f) < min)
		{
			result.pixelV[j].B = (unsigned char)0;
		}
		else if (((it.blue * 255) + 0.5f) > max)
		{
			result.pixelV[j].B = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].B = (unsigned char)(int)((it.blue * 255) + 0.5f);
		}
		if (((it.green * 255) + 0.5f) < min)
		{
			result.pixelV[j].G = (unsigned char)0;
		}
		else if (((it.green * 255) + 0.5f) > max)
		{
			result.pixelV[j].G = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].G = (unsigned char)(int)((it.green * 255) + 0.5f);
		}
		if (((it.red * 255) + 0.5f) < min)
		{
			result.pixelV[j].R = (unsigned char)0;
		}
		else if (((it.red * 255) + 0.5f) > max)
		{
			result.pixelV[j].R = (unsigned char)255;
		}
		else
		{
			result.pixelV[j].R = (unsigned char)(int)((it.red * 255) + 0.5f);
		}
		j++;
	}

	writeCopyOfImage(result);
}

void Image::writeImage(string one, string two, string three, string four)
{

	Image result;
	result.ImageName = "extracredit.tga";
	vector<Image> temp;
	readImage(one, temp);
	readImage(two, temp);
	readImage(three, temp);
	readImage(four, temp);

	//result.header = defaultHeader();
	result.header.width = (temp[0].header.width + temp[1].header.width);
	result.header.height = (temp[2].header.height + temp[3].header.height);
	int imageSize = (temp[0].header.width + temp[1].header.width) * (temp[2].header.height + temp[3].header.height);
	/*vector<Pixel> newPixel(imageSize);
	int currentPixel = 0;
	for (int i = 0; i < temp[0].header.width * temp[0].header.height; i++)
	{
	newPixel[i].B = temp[0].pixelV[i].B;
	newPixel[i].G = temp[0].pixelV[i].G;
	newPixel[i].R = temp[0].pixelV[i].R;
	currentPixel++;
	}
	for (int i = 0; i < temp[1].header.width * temp[1].header.height; i++)
	{
	newPixel[currentPixel].B = temp[1].pixelV[i].B;
	newPixel[currentPixel].G = temp[1].pixelV[i].G;
	newPixel[currentPixel].R = temp[1].pixelV[i].R;
	currentPixel++;
	}
	for (int i = 0; i < temp[2].header.width * temp[2].header.height; i++)
	{
	newPixel[currentPixel].B = temp[2].pixelV[i].B;
	newPixel[currentPixel].G = temp[2].pixelV[i].G;
	newPixel[currentPixel].R = temp[2].pixelV[i].R;
	currentPixel++;
	}
	for (int i = 0; i < temp[3].header.width * temp[3].header.height; i++)
	{
	newPixel[currentPixel].B = temp[3].pixelV[i].B;
	newPixel[currentPixel].G = temp[3].pixelV[i].G;
	newPixel[currentPixel].R = temp[3].pixelV[i].R;
	currentPixel++;
	}
	result.pixelV.resize(imageSize);
	int ct = 0;
	for (auto & it : result.pixelV)
	{
	it = newPixel[ct];
	}*/


	std::ofstream  dst("Output\\" + result.ImageName, std::ios::binary);
	dst.write((const char*)&result.header.idLength, sizeof(result.header.idLength));
	dst.write((const char*)&result.header.colourMapType, sizeof(result.header.colourMapType));
	dst.write((const char*)&result.header.dataTypeCode, sizeof(result.header.dataTypeCode));
	dst.write((const char*)&result.header.colourMapOrigin, sizeof(result.header.colourMapOrigin));
	dst.write((const char*)&result.header.colourMapLength, sizeof(result.header.colourMapLength));
	dst.write((const char*)&result.header.colourMapDepth, sizeof(result.header.colourMapDepth));
	dst.write((const char*)&result.header.xOrigin, sizeof(result.header.xOrigin));
	dst.write((const char*)&result.header.yOrigin, sizeof(result.header.yOrigin));
	dst.write((const char*)&result.header.width, sizeof(result.header.width));
	dst.write((const char*)&result.header.height, sizeof(result.header.height));
	dst.write((const char*)&result.header.bitsPerPixel, sizeof(result.header.bitsPerPixel));
	dst.write((const char*)&result.header.imageDescriptor, sizeof(result.header.imageDescriptor));

	//for (auto & it : result.pixelV)
	//{
	//	dst.write((const char*)&it.B, 1);
	//	dst.write((const char*)&it.G, 1);
	//	dst.write((const char*)&it.R, 1);
	//}
	for (auto & it : temp[0].pixelV)
	{
		dst.write((const char*)&it.B, 1);
		dst.write((const char*)&it.G, 1);
		dst.write((const char*)&it.R, 1);
	}
	for (auto & it : temp[1].pixelV)
	{
		dst.write((const char*)&it.B, 1);
		dst.write((const char*)&it.G, 1);
		dst.write((const char*)&it.R, 1);
	}
	for (auto & it : temp[2].pixelV)
	{
		dst.write((const char*)&it.B, 1);
		dst.write((const char*)&it.G, 1);
		dst.write((const char*)&it.R, 1);
	}
	for (auto & it : temp[3].pixelV)
	{
		dst.write((const char*)&it.B, 1);
		dst.write((const char*)&it.G, 1);
		dst.write((const char*)&it.R, 1);
	}

}