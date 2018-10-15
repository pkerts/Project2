#include "bitstreams.h"
#include <string>
#include <fstream>
#include <bitset>
#include <iostream>

Bitstreams::Bitstreams(const std::string& filename) : file_(new std::ofstream(filename, std::ios::binary))
{
}

Bitstreams::~Bitstreams()
{
	Flush();
	delete file_;
}

int Bitstreams::putBit(const unsigned int bit)
{
	buffer_ = (buffer_ << 1) | (bit & 1);
	position_++;
	if (position_ > 7)
	{
		file_->write(reinterpret_cast<char*>(&buffer_), sizeof(unsigned char));
		position_ = 0;
		buffer_ = 0;
	}
	return 0;
}

int Bitstreams::putByte(unsigned char byte)
{
	Flush();
	file_->write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	return 0;
}

int Bitstreams::putLong(uint32_t total) const
{
	file_->write(reinterpret_cast<char*>(&total), sizeof(uint32_t));
	return 0;
}

void Bitstreams::Flush()
{
	if (buffer_ || position_)
	{
		buffer_ <<= (8 - position_);
		file_->write(reinterpret_cast<char*>(&buffer_), sizeof(unsigned char));
		position_ = 0;
		buffer_ = 0;
	}
}
