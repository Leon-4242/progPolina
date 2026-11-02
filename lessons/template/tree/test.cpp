#include "tree.hpp"
#include <iostream>

int main()
{
	Tree<int, int> tree;

	tree.push(1, 1);
	tree.push(2, 2);
	tree.push(3, 3);
/*
	for (auto it = tree.rbegin(); it != tree.rend(); ++it)
	{
		std::cout << (*it).first << std::endl;
	}
*/
	return 0;
}
