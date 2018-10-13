#pragma once
#include <fstream>

class Bitreader
{
public:
	Bitreader(std::string filename);
	~Bitreader();
	int getBit();
	int getByte();
	int get_buffer() { return buffer; };
private:
	unsigned char buffer{ 0 };
	int position{ 0 };
	std::ifstream* file;
};

