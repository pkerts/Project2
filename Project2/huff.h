#pragma once
#include <fstream>
#include <string>
#include <climits>

class Huff
{
public:
	Huff(std::string filename);  // Create Huff object with filename as string parameter
	~Huff(); // Dtor which deletes ifstream pointer
	void BuildFrequencyTable(); // Single function so far which builds frequency table from file
	unsigned int FrequencyTable(int i) { return frequency_table_[i]; };
	unsigned char output_characters(unsigned long position_in_file);
	unsigned long get_total_characters();
private:
	std::ifstream* in_; // ifstream pointer which we initialize with string parameter from ctor
	unsigned int frequency_table_[UCHAR_MAX + 1] {0}; // Frequency table and initialize every element to 0 initially.
												  	  // So when we call ++ incrementer later we will achieve defined behavior
	unsigned long total_characters{0};
};