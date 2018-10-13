#include "puff.h"
#include "Bitreader.h"
#include <string>
#include <iostream>
#include <fstream>

Puff::Puff()
{
}


Puff::~Puff()
{
}

int main(int argc, char** argv)
{
	std::string filename = argv[1];
	Bitreader br(filename);

	std::ofstream puff("yes.puff", std::ios::binary);

	// TEST ok it works
	/*for (auto i = 0; i < 269; ++i)
	{
		auto a = br.getByte();
		puff.write((char*)&a, sizeof (char));
	}*/

	return 0;
}