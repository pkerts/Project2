#include "Bitreader.h"
#include <fstream>


Bitreader::Bitreader(const std::string& filename) : file_(new std::ifstream(filename, std::ios::binary))
{
}

Bitreader::~Bitreader()
= default;

int Bitreader::getBit()
{
	if (position_ == 0)
	{
		file_->read(reinterpret_cast<char*>(&buffer_), sizeof(unsigned char));
		position_ = 8;
	}
	position_--;
	const int bit = (buffer_ >> position_) & 1;
	return bit;
}

int Bitreader::getByte()
{
	buffer_ = 0;
	file_->read(reinterpret_cast<char*>(&buffer_), sizeof(unsigned char));
	position_ = 8;
	return buffer_;
}

int Bitreader::getBuffer() const
{
	return buffer_;
}

uint32_t Bitreader::getLength()
{
	uint32_t length = 0;
	file_->read(reinterpret_cast<char*>(&length), sizeof(uint32_t));
	buffer_ = 0;
	position_ = 0;
	return length;
}
