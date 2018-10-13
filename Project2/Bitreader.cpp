#include "Bitreader.h"
#include <fstream>


Bitreader::Bitreader(std::string filename) : file(new std::ifstream(filename, std::ios::binary))
{
}

Bitreader::~Bitreader()
{
}

int Bitreader::getBit()
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

int Bitreader::getByte()
{
	position = 0;
	buffer = 0;
	file->read(reinterpret_cast<char*>(&buffer), sizeof(unsigned char));
	return buffer;
}
