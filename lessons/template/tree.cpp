#include "tree.hpp"
#include <vector>
#include <iostream>

void test()
{
	Tree<int, int> tree;
	for (std::size_t i{}; i < 10000; ++i)
	{
		tree.push(i, i);
	}

	int (*func)(const int&) = [](const int& x){return x*(x+1)/2;};

	tree.map(func);

	for (std::size_t i{}; i < 10000; ++i)
	{
		std::cout << tree[i] << std::endl;
	}
}

int main()
{
	Tree<int, int> tree;
	tree.push(2, 3);
	tree.push(1, 4);
	int buff{};

	if (tree.search(1, buff))
	{
		std::cout << buff << std::endl;
	}
	else
	{
		std::cout << "Not found" << std::endl;
	}

	tree[1] = -3;

	if (tree.search(1, buff))
	{
		std::cout << buff << std::endl;
	}
	else
	{
		std::cout << "Not found" << std::endl;
	}


	return 0;
}
