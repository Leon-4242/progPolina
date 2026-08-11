#include <string>
#include <iostream>
#include <fstream>

bool check(int);

int function(std::ifstream in, double & result)
{
	double x = 0, sum = 0;
	while (in >> x)
	{
		if (x < 1e-15)
		{
			return -1;
		}
		result += x;
	}

	return 0;
}

int main()
{
	std::string str;
	str = "14";
	str += "15";
	std::cin >> str;
	str += " 15";
	std::cout << str << "\n";

	int * array = new int[5];
	for (int i = 0; i < 5; ++i)
	{
		array[i] = i*i;
		if (!check(i))
		{
			continue;
		}
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	function(in, result);

	delete[] array;
	return 0;
}

bool check(int k)
{
	if (k == 3)
		return true;
	else 
		return false;
}
