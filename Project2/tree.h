#pragma once
#include <vector>

class tree
{
private:
	struct TreeNode
	{
		unsigned int priority;
		unsigned char data;
		TreeNode* left;
		TreeNode* right;
	};
	TreeNode* root = nullptr;
	std::vector<TreeNode> tree_node_vector_;
public:
	void Add(unsigned int a, unsigned char b, unsigned int c, unsigned char d);
	
};
