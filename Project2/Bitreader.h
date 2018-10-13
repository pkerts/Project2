#pragma once
#include <fstream>

class Bitreader
{
public:
	Bitreader(std::string filename);
	~Bitreader();
	int getBit();
	int getByte();
private:
	unsigned char buffer{ 0 };
	int position{ 0 };
	std::ifstream* file;
};

