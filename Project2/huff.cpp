#include "huff.h"
#include "Heap.h"
#include "tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "bitstreams.h"
#include <cmath>

Huff::Huff(const std::string& filename) : in_(new std::ifstream(filename))
// Initialize ifstream object immediately when ctor for Huff is called
{
	BuildFrequencyTable();
	// Build our frequency table using the text file provided in the bash command line argument and passed to Huff ctor
}

Huff::~Huff() // dtor which deletes ifstream pointer
{
	delete in_;
}

void Huff::BuildFrequencyTable() // Build frequency table
{
	if (in_->is_open())
	{
		// Check first just to make sure file is open. (File is passed in from Huff constructor
		// which is acquired from argv, command line parameter. Ex. ./a.out textfile.txt
		std::ifstream::pos_type pos = 0;
		while (in_->peek() != -1)
		{
			// While a character is still available in the text, acquire it, 
			// until there are no characters left in the text file.
			const unsigned char unsigned_ch = in_->peek();
			frequency_table_[static_cast<int>(unsigned_ch)]++;
			// For the index in the frequency table corresponding to the ASCII value 
			// of the current character, increment it by 1. (To eventually get a 
			// definitive character count
			total_characters_++;
			pos += 1;
			in_->seekg(pos);
		}
	}
	in_->seekg(0);

	// TEST
	// Parse through the frequency table after building it is done and print characters that were found
	// (if they are printable) and their corresponding frequencies.
	int total = 0;
	for (auto i = 0; i < 256; ++i)
	{
		if (frequency_table_[i] != 0) // If there was this particular character found
		{
			if (isprint(static_cast<char>(i))) // If this character is printable, print it
			{
				std::cout << static_cast<char>(i) << " ";
			}
			else
			{
				std::cout << "NA "; // Otherwise print "NA"
			}
			std::cout << " (" << std::hex << std::showbase << std::uppercase << i << ") " << std::dec <<
				frequency_table_[i] << std::endl; // Print the frequency of this character
			total += frequency_table_[i];
		}
	}
	std::cout << "total: " << total << std::endl;
}

unsigned Huff::FrequencyTable(const int i)
{
	return frequency_table_[i];
}

unsigned char Huff::OutputCharacters(const unsigned long position_in_file) const
{
	in_->seekg(position_in_file);
	const unsigned char ch = in_->peek();
	return ch;
}

unsigned long Huff::GetTotalCharacters() const
{
	return total_characters_;
}

int main(int argc, char** argv) // The compiled code will take an argument
{
	std::string filename = argv[1];
	// Get the string form of the argument. (This will be our filename. Ex. "./a.out textfile.txt" It
	// is the textfile.txt part)

	Huff h(filename); // Create Huff object using the argv. It goes argv > string > file opened
	Heap<unsigned int, unsigned char> heap;
	for (auto i = 0; i < 256; ++i)
	{
		if (h.FrequencyTable(i))
		{
			heap.Push(h.FrequencyTable(i), static_cast<unsigned char>(i), nullptr, nullptr);
		}
	}
	heap.Print();
	heap.MakeTree();
	heap.CheckTree();
	heap.CreateCodedSymbols();
	heap.PrintBitPatterns();

	filename.append(".huff");
	Bitstreams bs(filename);

	// WRITING THE HEADER
	for (auto ascii_value = 0; ascii_value < 256; ++ascii_value)
	{
		const auto bitlength = heap.ReturnBitLength(ascii_value);
		bs.putByte(bitlength);
		for (auto position = (bitlength - 1); position > -1; --position)
		{
			bs.putBit(heap.ReturnBitpatternBitByBit(ascii_value, position));
		}
		bs.Flush();
	}
	bs.Flush();

	// WRITING THE NUMBER OF SYMBOLS IN THE FILE
	const auto total_characters = h.GetTotalCharacters();
	bs.putLong(total_characters);

	// WRITING THE SYMBOLS
	int bitswritten = 0;

	for (unsigned int position_in_file = 0; position_in_file < total_characters; ++position_in_file)
	{
		const auto ch = h.OutputCharacters(position_in_file);
		const unsigned int length = heap.ReturnBitLength(static_cast<unsigned int>(ch));
		for (int bitposition = (length - 1); bitposition > -1; --bitposition)
		{
			bs.putBit(heap.ReturnBitpatternBitByBit(static_cast<int>(ch), bitposition));
			++bitswritten;
			std::cout << ch << " " << "bit: " << heap.ReturnBitpatternBitByBit(static_cast<int>(ch), bitposition) <<
				"num: " << bitswritten << std::endl;
		}
		std::cout << std::endl;
		bitswritten = 0;
	}

	return 0;
}
