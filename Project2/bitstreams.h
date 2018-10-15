#pragma once
#include <fstream>
#include <string>

class Bitstreams
{
public:
	explicit Bitstreams(const std::string& filename);
	~Bitstreams();

	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	int putLong(uint32_t total) const;
	void Flush();
private:
	unsigned char buffer_{0};
	int position_{0};
	std::ofstream* file_;
};
