#pragma once
#include <vector>

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
public:
	bool is_empty();
	void push();
};

template <typename Priority, typename Data>
void Heap<Priority, Data>::push()
{
	Node n{ 1, 2 };
	data_vector_.emplace_back(n);
}

template <typename Priority, typename Data>
bool Heap<Priority, Data>::is_empty()
{
	return data_vector_.size();
}