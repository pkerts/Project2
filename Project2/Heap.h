#pragma once
#include <vector>
#include <iostream>
#include <ctype.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <bitset>

template <typename Priority, typename Data>
class Heap
{
private:
	struct Node
	{
		Priority priority;
		Priority data;
		Node* left;
		Node* right;
	};

	struct CodedSymbol
	{
		unsigned char length;
		unsigned long long bit_pattern;
	};

	CodedSymbol coded_symbols_array[256]{{0, 0}};
	std::vector<Node> data_vector_;
	void Heapify(int i);
	Node* minimum_ = nullptr;
	Node* root_ = nullptr;
	int CheckTree(Node* ptr);
	void CreateCodedSymbols(Node* ptr, unsigned char length, unsigned long long bitpattern);
	void DeleteTree(Node* ptr);
public:
	~Heap();

	bool IsEmpty();
	void Push(Priority priority, Data data, Node* left, Node* right);
	Node* Pop();
	static int Parent(int i);
	static int LeftChild(int i);
	static int RightChild(int i);
	int Print();
	void Heapify();
	void Verify();
	void MakeTree();
	void CheckTree();
	std::string NodeDump(unsigned int i);
	void CreateCodedSymbols();
	void PrintBitPatterns();
	unsigned char ReturnBitLength(unsigned int i);
	unsigned int ReturnBitpatternBitByBit(unsigned int i, int position);
	unsigned int ReturnBitLengthBitByBit(unsigned int i, int position);
};

template <typename Priority, typename Data>
void Heap<Priority, Data>::Push(Priority priority, Data data, Node* left, Node* right)
{
	data_vector_.push_back({priority, data, left, right});
	Heapify(data_vector_.size() - 1);
}

template <typename Priority, typename Data>
typename Heap<Priority, Data>::Node* Heap<Priority, Data>::Pop()
{
	auto min_priority = std::min_element(data_vector_.begin(), data_vector_.end(),
	                                     [](Node const& lhs, Node const& rhs) { return lhs.priority < rhs.priority; });
	minimum_ = new Node{*min_priority};
	data_vector_.erase(min_priority);
	for (const auto i : data_vector_)
	{
		if (i.priority < minimum_->priority)
		{
			std::cout << "Uh oh" << std::endl;
			for (auto a = 0; a < 4; ++a)
			{
				std::cout << "----" << std::endl;
			}
		}
	}
	return minimum_;
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::Parent(const int i)
{
	return ((i - 1) / 2);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::LeftChild(const int i)
{
	if (i == 0) // root case
	{
		return 1;
	}
	return (i * 2 + 1);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::RightChild(const int i)
{
	if (i == 0) // root case
	{
		return 2;
	}
	return (i * 2 + 2);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::Print()
{
	if (IsEmpty())
	{
		std::cerr << "Empty vector" << std::endl;
		return 1;
	}
	std::cout << "root: ";

	auto level = 1;
	auto a = 0;
	auto b = level;

	for (unsigned int i = 0; i < data_vector_.size(); ++i)
	{
		if (a == b)
		{
			b = std::pow(2, level);
			a = 0;
			level++;
			std::cout << " level " << level << ":  ";
		}
		std::cout << NodeDump(i) << " ";
		a++;
	}
	std::cout << std::endl;
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::Heapify()
{
	Heapify(data_vector_.size());
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::Verify()
{
	auto tru = 0;
	for (auto i = data_vector_.size() - 1; i > 0; --i)
	{
		if (data_vector_[Parent(i)].priority < data_vector_[i].priority)
		{
			std::cout << "FALSE" << std::endl;
		}
		else
		{
			tru++;
		}
	}
	std::cout << "TRUE X" << tru << std::endl;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::MakeTree()
{
	while (data_vector_.size() > 1)
	{
		auto* a = new Node{*Pop()};
		auto b = a->priority;
		auto* d = new Node{*Pop()};
		auto e = d->priority;

		Push((b + e), '\0', a, d);
	}
	root_ = &data_vector_.front();
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::CheckTree()
{
	CheckTree(root_);
}

template <typename Priority, typename Data>
std::string Heap<Priority, Data>::NodeDump(unsigned int i)
{
	std::string dump;
	if ((i < 0) | (i >= data_vector_.size()))
	{
		return dump;
	}
	dump.append(std::to_string(data_vector_[i].priority));
	dump.push_back(',');
	if (isprint(data_vector_[i].data))
	{
		dump.push_back(data_vector_[i].data);
	}
	else
	{
		dump.append("NA");
	}
	return dump;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::Heapify(int i)
{
	while (i != 0)
	{
		if (data_vector_[Parent(i)].priority > data_vector_[i].priority)
		{
			std::swap(data_vector_[Parent(i)], data_vector_[i]);
		}
		i = Parent(i);
		Heapify(i);
	}
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::CheckTree(Node* ptr)
{
	if (ptr->left)
	{
		CheckTree(ptr->left);
	}
	if (ptr->data)
	{
		std::cout << ptr->data << std::endl;
	}
	if (ptr->right)
	{
		CheckTree(ptr->right);
	}
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::CreateCodedSymbols()
{
	CreateCodedSymbols(root_, 0, 0);
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::PrintBitPatterns()
{
	for (auto i = 0; i < 256; ++i)
	{
		if (coded_symbols_array[i].length)
		{
			std::bitset<12> bb{coded_symbols_array[i].bit_pattern};
			std::cout << "'" << static_cast<unsigned char>(i) << "'" << " " << "length: " << static_cast<int>(
				coded_symbols_array[i].length) << " ";
			std::cout << bb.to_string() << std::endl;
		}
		std::cout << i << std::endl;
	}
}

template <typename Priority, typename Data>
unsigned char Heap<Priority, Data>::ReturnBitLength(unsigned i)
{
	return coded_symbols_array[i].length;
}

template <typename Priority, typename Data>
unsigned Heap<Priority, Data>::ReturnBitpatternBitByBit(unsigned i, const int position)
{
	auto a = coded_symbols_array[i].bit_pattern;
	unsigned long long b = 1;
	b <<= (position);
	if (a & b)
	{
		return 1;
	}
	return 0;
}

template <typename Priority, typename Data>
unsigned Heap<Priority, Data>::ReturnBitLengthBitByBit(unsigned i, const int position)
{
	auto a = coded_symbols_array[i].length;
	unsigned long long b = 1;
	b <<= (position);
	if (a & b)
	{
		return 1;
	}
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::CreateCodedSymbols(Node* ptr, unsigned char length, const unsigned long long bitpattern)
{
	if (ptr == nullptr)
	{
		return;
	}

	if (!(ptr->left) && !(ptr->right))
	{
		// TEST
		std::bitset<8> bp{bitpattern};
		std::cout << "\"" << ptr->data << "\"  " << "\"" << static_cast<char>(ptr->data) << "\"  " << "\"" <<
			static_cast<int>(ptr->priority) << "\"  " << "\"" << bp.to_string() << "\"  " << "\"" << static_cast<int>(
				length) << "\"" << std::endl;
		CodedSymbol cs{length, bitpattern};
		coded_symbols_array[static_cast<int>(ptr->data)] = cs;
	}

	length++;
	if (ptr->left)
		CreateCodedSymbols(ptr->left, length, bitpattern << 1);
	if (ptr->right)
		CreateCodedSymbols(ptr->right, length, (bitpattern << 1) | 1);
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::DeleteTree(Node* ptr)
{
	if (ptr->left)
	{
		DeleteTree(ptr->left);
	}
	if (ptr->right)
	{
		DeleteTree(ptr->right);
	}
	delete ptr;
}

template <typename Priority, typename Data>
Heap<Priority, Data>::~Heap()
{
	// delete_tree(root);
	delete minimum_;
}

template <typename Priority, typename Data>
bool Heap<Priority, Data>::IsEmpty()
{
	return data_vector_.empty();
}
