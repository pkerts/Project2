#pragma once
#include <fstream>
#include <string>

class bitstreams
{
public:
	bitstreams(std::string filename);
	~bitstreams();

	int getBit();
	int getByte();
	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
private:
	unsigned char buffer{ 0 };
	int position{ 0 };
	std::ifstream* file;
};

