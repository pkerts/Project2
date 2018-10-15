#pragma once
#include <fstream>
#include <string>

class Bitstreams
{
public:
	Bitstreams(const std::string& filename);
	~Bitstreams();

	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	int putLong(uint32_t total) const;
	void Flush();
private:
	unsigned char buffer{0};
	int position{0};
	std::ofstream* file;
};
