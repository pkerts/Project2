#include "bitstreams.h"
#include <string>
#include <fstream>


bitstreams::bitstreams(std::string filename) : file(new std::fstream(filename, std::ios::in | std::ios::out | std::ios::binary))
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
	int bit = (buffer >> position) & 1;
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
	position++;
	if (position > 7) {
		file->write(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
		position = 0;
		buffer = 0;
	}
	return 0;
}

int bitstreams::putByte(unsigned char byte)
{
	buffer <<= (8 - position);
	file->write(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
	position = 0;
	buffer = 0;
	file->write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	return 0;
}
