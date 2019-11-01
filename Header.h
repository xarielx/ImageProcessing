#pragma once
struct Header
{
	char idLength;
	char colourMapType;
	char dataTypeCode;
	short colourMapOrigin;
	short colourMapLength;
	char colourMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;

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
};

