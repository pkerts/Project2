#pragma once
#include <fstream>

class Bitreader
{
public:
	explicit Bitreader(const std::string& filename);
	~Bitreader();
	int getBit();
	int getByte();
	int getBuffer() const;
	uint32_t getLength() const;
private:
	unsigned char buffer_{0};
	int position_{0};
	std::ifstream* file_;
};
