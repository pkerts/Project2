#pragma once
#include <vector>
#include <iostream>
#include <ctype.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <bitset>

template<typename Priority, typename Data>
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
	CodedSymbol coded_symbols_array[256];
	std::vector<Node> data_vector_;
	void heapify(int i);
	Node* minimum = nullptr;
	Node* root = nullptr;
	int check_Tree(Node* root);
	void create_coded_symbols(Node* Ptr, unsigned char length, unsigned long long bitpattern);
public:
	bool is_empty();
	void push(Priority priority, Data data, Node* right, Node* left);
	Node* pop();
	int parent(int i);
	int left_child(int i);
	int right_child(int i);
	int print();
	void heapify();
	void verify();
	void MakeTree();
	void check_Tree();
	std::string node_dump(unsigned int i);
	void create_coded_symbols();
	void print_bit_patterns();
	unsigned char return_bit_length(unsigned int i);
	unsigned int return_bitpattern_bit_by_bit(unsigned int i, int position);

};

template <typename Priority, typename Data>
void Heap<Priority, Data>::push(Priority priority, Data data, Node* left, Node* right)
{
	data_vector_.push_back({ priority, data, left, right });
	heapify(data_vector_.size() - 1);
}

template <typename Priority, typename Data>
typename Heap<Priority, Data>::Node* Heap<Priority, Data>::pop()
{
	auto min_priority = std::min_element(data_vector_.begin(), data_vector_.end(),
		[](Node const& lhs, Node const& rhs) {return lhs.priority < rhs.priority; });
	minimum = new Node{ *min_priority };
	data_vector_.erase(min_priority);
	for (const auto i : data_vector_)
	{
		if (i.priority < minimum->priority)
		{
			std::cout << "Uhoh" << std::endl;
			for (auto a = 0; a < 4; ++a)
			{
				std::cout << "----" << std::endl;
			}
		}
	}
	return minimum;
}

template<typename Priority, typename Data>
int Heap<Priority, Data>::parent(int i)
{
	return ((i - 1) / 2);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::left_child(int i)
{
	if (i == 0) // root case
	{
		return 1;
	}
	return (i * 2 + 1);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::right_child(int i)
{
	if (i == 0) // root case
	{
		return 2;
	}
	return (i * 2 + 2);
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::print()
{
	if (is_empty())
	{
		std::cerr << "Empty vector" << std::endl;
		return 1;
	}
	std::cout << "root: ";

	int level = 1;
	int a = 0;
	int b = level;

	for (unsigned int i = 0; i < data_vector_.size(); ++i)
	{
		if (a == b)
		{
			b = std::pow(2, level);
			a = 0;
			level++;
			std::cout << " level " << level << ":  ";
		}
		std::cout << node_dump(i) << " ";
		a++;
	}
	std::cout << std::endl;
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::heapify()
{
	heapify(data_vector_.size());
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::verify()
{
	int tru = 0;
	for (auto i = data_vector_.size()-1; i > 0; --i)
	{
		if (data_vector_[parent(i)].priority < data_vector_[i].priority)
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
		Node* a = new Node{ *pop() };
		auto b = a->priority;
		Node* d = new Node{ *pop() };
		auto e = d->priority;

		push((b + e), '\0', a, d);
	}
	root = &data_vector_.front();
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::check_Tree()
{
	check_Tree(root);
}

template <typename Priority, typename Data>
std::string Heap<Priority, Data>::node_dump(unsigned int i)
{
	std::string dump{ "" };
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
void Heap<Priority, Data>::heapify(int i)
{
	while (i != 0)
	{
		if (data_vector_[parent(i)].priority > data_vector_[i].priority)
		{
			std::swap(data_vector_[parent(i)], data_vector_[i]);
		}
		i = parent(i);
		heapify(i);
	}
}

template <typename Priority, typename Data>
int Heap<Priority, Data>::check_Tree(Node* Ptr)
{
	if (Ptr->left)
	{
		check_Tree(Ptr->left);
	}
	if (Ptr->data)
	{
		std::cout << Ptr->data << std::endl;
	}
	if (Ptr->right)
	{
		check_Tree(Ptr->right);
	}
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::create_coded_symbols()
{
	create_coded_symbols(root, 0, 0);
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::print_bit_patterns()
{
	for (auto i = 0; i < 256; ++i)
	{
		if (coded_symbols_array[i].bit_pattern)
		{
			std::bitset<12> bb{ coded_symbols_array[i].bit_pattern };
			std::cout << static_cast<int>(coded_symbols_array[i].length) << std::endl;
			std::cout << bb.to_string() << std::endl;
		}
	}
}

template <typename Priority, typename Data>
unsigned char Heap<Priority, Data>::return_bit_length(unsigned i)
{
	return coded_symbols_array[i].length;
}

template <typename Priority, typename Data>
unsigned Heap<Priority, Data>::return_bitpattern_bit_by_bit(unsigned i, int position)
{
	auto a = coded_symbols_array[i].bit_pattern;
	unsigned long long b = 1;
	b <<= (position-1);
	if (a & b)
	{
		return 1;
	}
	return 0;
}

template <typename Priority, typename Data>
void Heap<Priority, Data>::create_coded_symbols(Node* Ptr, unsigned char length, unsigned long long bitpattern)
{
	if (Ptr == nullptr)
	{
		return;
	}

	if (!(Ptr->left) && !(Ptr->right))
	{
		CodedSymbol cs{ length, bitpattern };
		coded_symbols_array[static_cast<int>(Ptr->data)] = cs;
	}

	length++;

	create_coded_symbols(Ptr->left, length, bitpattern << 1 | 1);
	create_coded_symbols(Ptr->right, length, bitpattern << 1);
}

template <typename Priority, typename Data>
bool Heap<Priority, Data>::is_empty()
{
	if (data_vector_.size())
	{
		return false;
	}
	return true;
}
