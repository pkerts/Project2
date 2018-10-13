#include "huff.h"
#include "Heap.h"
#include "tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "bitstreams.h"
#include <cmath>

Huff::Huff(std::string filename) : in_(new std::ifstream(filename)) // Initialize ifstream object immediately when ctor for Huff is called
{
	BuildFrequencyTable(); // Build our frequency table using the text file provided in the bash command line argument and passed to Huff ctor
}

Huff::~Huff() // dtor which deletes ifstream pointer
{
	delete in_;
}

void Huff::BuildFrequencyTable() // Build frequency table
{
	unsigned char unsigned_ch; // unsigned char we will use to make sure our ASCII values range correctly from 0-255 (instead of -127-128)

	if (in_->is_open()) { // Check first just to make sure file is open. (File is passed in from Huff constructor
						  // which is acquired from argv, command line parameter. Ex. ./a.out textfile.txt
		std::ifstream::pos_type pos = 0;
		while (in_->peek() != -1) { // While a character is still available in the text, acquire it, 
							  // until there are no characters left in the text file.
			unsigned_ch = in_->peek();
			frequency_table_[static_cast<int>(unsigned_ch)]++; // For the index in the frequency table corresponding to the ASCII value 
													 // of the current character, increment it by 1. (To eventually get a 
													 // definitive character count
			total_characters++;
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
			std::cout << " (" << std::hex << std::showbase << std::uppercase << i << ") " << std::dec << frequency_table_[i] << std::endl; // Print the frequency of this character
			total += frequency_table_[i];
		}
	}
	std::cout << "total: " << total << std::endl;

	// in_->close(); // Close the file
}

unsigned char Huff::output_characters(unsigned long position_in_file)
{
	in_->seekg(position_in_file);
	unsigned char ch = in_->peek();
	return ch;
}

unsigned long Huff::get_total_characters()
{
	return total_characters;
}

//int main(int argc, char** argv) // The compiled code will take an argument
//{
//	std::string filename = argv[1]; // Get the string form of the argument. (This will be our filename. Ex. "./a.out textfile.txt" It
//	// is the textfile.txt part)
//
//	// TEST/PLAYING AROUND
//	// readCharFile(filename);
//
//	Huff h(filename); // Create Huff object using the argv. It goes argv > string > file opened
//
//	// h.check_file();
//
//	Heap<unsigned int, unsigned char> heap;
//
//	for (auto i = 0; i < 256; ++i)
//	{
//		if (h.FrequencyTable(i))
//		{
//			heap.push(h.FrequencyTable(i), static_cast<unsigned char>(i), nullptr, nullptr);
//		}
//	}
//
//	heap.print();
//
//	heap.MakeTree();
//	heap.check_Tree();
//	heap.create_coded_symbols();
//	// tree tr;
//	heap.print_bit_patterns();
//
//
//	filename.replace(filename.find(".txt"), std::string(".txt").size(), ".huff");
//	bitstreams bs(filename);
//
//	// WRITING THE HEADER
//	for (auto ascii_value = 0; ascii_value < 256; ++ascii_value)
//	{
//		auto bitlength = heap.return_bit_length(ascii_value);
//		/*if (bitlength)
//		{
//			for (auto pos = 0; pos < 8; ++pos)
//			{
//				bs.putBit(heap.return_bit_length_bit_by_bit(ascii_value, pos));
//			}
//		}
//		else
//		{*/
//		bs.putByte(bitlength);
//		// }
//		// auto num_of_bytes = std::ceil(static_cast<double>(bitlength) / static_cast<double>(8));
//		for (auto position = (bitlength - 1); position > -1; --position)
//		{
//			bs.putBit(heap.return_bitpattern_bit_by_bit(ascii_value, position));
//		}
//		bs.flush();
//	}
//	bs.flush();
//
//	// WRITING THE NUMBER OF SYMBOLS IN THE FILE
//	auto total_characters = h.get_total_characters();
//	bs.putLong(total_characters);
//
//	unsigned char ch{ 0 };
//	unsigned int length = 0;
//	// WRITING THE SYMBOLS
//
//	int bitswritten = 0;
//
//	// YO
//	// THIS MIGHT NEED TO BE BIG ENDIAN
//	for (unsigned int position_in_file = 0; position_in_file < total_characters; ++position_in_file)
//	{
//		ch = h.output_characters(position_in_file);
//		length = heap.return_bit_length(static_cast<unsigned int>(ch));
//		for (int bitposition = (length-1); bitposition > -1; --bitposition)
//		{
//			bs.putBit(heap.return_bitpattern_bit_by_bit(static_cast<int>(ch), bitposition));
//			++bitswritten;
//			std::cout << ch << " " << "bit: " << heap.return_bitpattern_bit_by_bit(static_cast<int>(ch), bitposition) << "num: " << bitswritten << std::endl;
//		}
//		std::cout << std::endl;
//		bitswritten = 0;
//	}
//
//
//	// in
//
//	// Heap heap(huff.fre)
//	/*Heap<int, int> heap;
//	heap.push();
//	heap.push();
//	heap.push();
//	heap.push();
//	heap.push();*/
//
//	// std::cout << heap.is_empty();
//
//	// START OF A TEST/PLAYING AROUND SNIPPET
//	//std::cout << filename;
//	//std::cout << "hello test";
//	//std::fstream file(filename);
//	//std::string test;
//	//*for (std::string line; getline(input, line); )
//	//{
//	//	...for each line in input...
//	//}*/
//	//char buffer{0};
//	//// for (auto i = 0; i < 4; ++i)
//	//// {
//	//	std::getline(file, test);
//	//	std::cout << test;
//	//// }
//	// END OF A TEST SNIPPET
//
//
//	return 0;
//}
