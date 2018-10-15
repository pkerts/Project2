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

	Node* root_;
	Node* position_;
	static int Checktree(Node* ptr, int status);
public:
	Puff();
	~Puff();
	int Filltree(unsigned int bit);
	int SetNode(char data);
	int Checktree() const;
};
