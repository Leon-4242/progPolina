#include <iostream>

void func (int & k)
{
	++k;
}

int main()
{
	int a = 4;

	int & b = a;

	b = 6;

	std::cout << a << std::endl;
	return 0;
}
