#include "bitstreams.h"
#include <string>
#include <fstream>


bitstreams::bitstreams(std::string filename) : file(new std::ifstream(filename, std::ios::binary))
{
}


bitstreams::~bitstreams()
{
	delete file;
}

int bitstreams::getBit()
{
	if (position == 0)
	{
		file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
		position = 8;
	}
	position--;
	int bit = (bit >> position) & 1;
	return bit;
}

int bitstreams::getByte()
{
	position = 0;
	buffer = 0;
	file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
	return buffer;
}

int bitstreams::putBit(unsigned int bit)
{
	buffer = (buffer << 1) | (bit & 1);
	if (position > 7) {
		// write buffer
		// count = 0
		// buffer = 0
	}

	return 0;
}

int bitstreams::putByte(unsigned char byte)
{
	// pad buffer using count
	// write buffer
	// write byte param
	return 0;
}
