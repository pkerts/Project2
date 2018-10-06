#include "tree.h"

void tree::Add(unsigned a, unsigned char b, unsigned c, unsigned char d)
{
	TreeNode* left = new TreeNode{ a, b };
	TreeNode* right = new TreeNode{ c, d };
	tree_node_vector_.push_back({ '\0', '\0', left, right });
}
