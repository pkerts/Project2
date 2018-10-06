#pragma once
#include <vector>
#include <iostream>
#include <ctype.h>
#include <string>
#include <cmath>

template<typename Priority, typename Data>
class Heap
{
private:
	struct Node
	{
		Priority priority;
		Priority data;
	};
	std::vector<Node> data_vector_;
	void heapify(int i);
	Node* minimum = nullptr;
public:
	bool is_empty();
	void push(Priority priority, Data data);
	Node* pop();
	int parent(int i);
	int left_child(int i);
	int right_child(int i);
	int print();
	void heapify();
	void verify();
	std::string node_dump(unsigned int i);
};

template <typename Priority, typename Data>
void Heap<Priority, Data>::push(Priority priority, Data data)
{
	data_vector_.push_back({ priority, data });
	heapify(data_vector_.size() - 1);
}

template <typename Priority, typename Data>
typename Heap<Priority, Data>::Node* Heap<Priority, Data>::pop()
{
	minimum = new Node{ data_vector_.back() };
	data_vector_.pop_back();
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
		if (data_vector_[parent(i)].priority < data_vector_[i].priority)
		{
			std::swap(data_vector_[parent(i)], data_vector_[i]);
		}
		i = parent(i);
		heapify(i);
	}
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
