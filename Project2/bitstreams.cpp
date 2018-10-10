#include "bitstreams.h"
#include <string>
#include <fstream>
#include <bitset>
#include <iostream>


bitstreams::bitstreams(std::string filename) : file(new std::ofstream(filename, /*std::ios::in | std::ios::out | */std::ios::binary))
{
}


bitstreams::~bitstreams()
{
	flush();
	delete file;
}

//int bitstreams::getBit()
//{
//	if (position == 0)
//	{
//		file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
//		position = 8;
//	}
//	position--;
//	int bit = (buffer >> position) & 1;
//	return bit;
//}

//int bitstreams::getByte()
//{
//	position = 0;
//	buffer = 0;
//	file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
//	return buffer;
//}

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
	flush();
	file->write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	return 0;
}

int bitstreams::putLong(unsigned long total)
{
	std::cout << std::endl;
	unsigned char mask = { 0b11111111 };
	for (auto i = 3; i >= 0; --i)
	{
		putByte(total >> (8 * i) & mask);
	}
	return 0;
}

void bitstreams::flush()
{
	if (buffer || position)
	{
		buffer <<= (8 - position);
		file->write(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
		position = 0;
		buffer = 0;
	}
}
