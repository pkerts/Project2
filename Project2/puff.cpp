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

int Puff::filltree(unsigned int bit)
{
	if (!root)
	{
		root = new Node{ '\0', nullptr, nullptr };
		position = root;
	}
	if (bit == 0)
	{
		if (!position->left)
		{
			position->left = new Node{ '\0', nullptr, nullptr };
		}
		position = position->left;
	}
	else
	{
		if (!position->right)
		{
			position->right = new Node{ '\0', nullptr, nullptr };
		}
		position = position->right;
	}
	return 0;
}

int Puff::set_node(char data)
{
	position->data = data;
	position = root;
	return 0;
}

int main(int argc, char** argv)
{
	std::string filename = argv[1];
	Bitreader br(filename);

	filename.replace(filename.find(".huff"), std::string(".huff").size(), ".puff");
	std::ofstream puff(filename, std::ios::binary);

	// TEST ok it works
	/*for (auto i = 0; i < 269; ++i)
	{
		auto a = br.getByte();
		puff.write((char*)&a, sizeof (char));
	}*/

	Puff p;

	auto ascii_value = -1;
	auto length = 0;
	while (ascii_value != 255)
	{
		br.getByte();
		ascii_value++;
		if (br.get_buffer())
		{
			length = br.get_buffer();
			br.getByte();
			std::cout << static_cast<char>(ascii_value) << "   ";
			for (auto i = 0; i < length; i++)
			{
				p.filltree(br.getBit());
			}
			p.set_node(static_cast<char>(ascii_value));
			std::cout << std::endl;
		}
	}

	return 0;
}
