#pragma once

class Puff
{
private:
	struct Node
	{
		char data;
		Node* left;
		Node* right;
	};
	Node* root;
	Node* position;
public:
	Puff();
	~Puff();
	int filltree(unsigned int bit);
	int set_node(char data);
};

