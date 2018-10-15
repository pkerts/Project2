#include "puff.h"
#include "Bitreader.h"
#include <string>
#include <iostream>
#include <fstream>


Puff::Puff(): root_(nullptr), position_(nullptr)
{
}


Puff::~Puff()
= default;

int Puff::Filltree(unsigned int bit)
{
	if (!root_)
	{
		root_ = new Node{'\0', nullptr, nullptr};
		position_ = root_;
	}
	if (bit == 0)
	{
		if (!position_->left)
		{
			position_->left = new Node{'\0', nullptr, nullptr};
		}
		position_ = position_->left;
	}
	else
	{
		if (!position_->right)
		{
			position_->right = new Node{'\0', nullptr, nullptr};
		}
		position_ = position_->right;
	}
	return 0;
}

int Puff::SetNode(char data)
{
	position_->data = data;
	position_ = root_;
	return 0;
}

int Puff::Checktree() const
{
	if (!root_)
	{
		std::cerr << "Nothing in tree" << std::endl;
		return 1;
	}
	return Checktree(root_, 0);
}

int Puff::Checktree(Node* ptr, int status)
{
	if (ptr == nullptr)
	{
		return status;
	}

	if (ptr->data == '\0')
	{
		if (!ptr->left)
		{
			// TRY PRINTING ADDRESS HERE
			std::cerr << "Missing left child" << std::endl;
			status = 1;
		}
		if (!ptr->right)
		{
			std::cerr << "Missing right child" << std::endl;
			status = 1;
		}
	}
	if (ptr->data) // redundant if?
	{
		if (ptr->left || ptr->right)
		{
			std::cerr << "Data detected in a non-leaf node" << std::endl;
			status = 2;
		}
	}

	Checktree(ptr->left, status);
	Checktree(ptr->right, status);
	return status;
}

int main(int argc, char** argv)
{
	std::string filename = argv[1];
	Bitreader br(filename);

	filename.replace(filename.find(".huff"), std::string(".huff").size(), ".puff");
	std::ofstream puff(filename, std::ios::binary);

	Puff p;

	auto ascii_value = -1;
	while (ascii_value != 255)
	{
		br.getByte();
		ascii_value++;
		if (br.getBuffer())
		{
			const int length = br.getBuffer();
			br.getByte();
			std::cout << static_cast<char>(ascii_value) << "   ";
			for (auto i = 0; i < length; i++)
			{
				p.Filltree(br.getBit());
			}
			p.SetNode(static_cast<char>(ascii_value));
			std::cout << std::endl;
		}
	}

	if (p.Checktree() != 0)
	{
		return EXIT_FAILURE;
	}

	// length = br.getLength();

	return 0;
}
