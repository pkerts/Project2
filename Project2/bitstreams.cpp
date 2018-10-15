#include "bitstreams.h"
#include <string>
#include <fstream>
#include <bitset>
#include <iostream>

Bitstreams::Bitstreams(const std::string& filename) : file(new std::ofstream(filename, std::ios::binary))
{
}

Bitstreams::~Bitstreams()
{
	Flush();
	delete file;
}

int Bitstreams::putBit(const unsigned int bit)
{
	buffer = (buffer << 1) | (bit & 1);
	position++;
	if (position > 7)
	{
		file->write(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
		position = 0;
		buffer = 0;
	}
	return 0;
}

int Bitstreams::putByte(unsigned char byte)
{
	Flush();
	file->write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	return 0;
}

int Bitstreams::putLong(uint32_t total) const
{
	file->write(reinterpret_cast<char*>(&total), sizeof(uint32_t));
	return 0;
}

void Bitstreams::Flush()
{
	if (buffer || position)
	{
		buffer <<= (8 - position);
		file->write(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
		position = 0;
		buffer = 0;
	}
}
