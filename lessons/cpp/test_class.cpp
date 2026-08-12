#include "class.hpp"
#include <iostream>

int square(const Person &);
void birthday (Person &);

int main()
{
	Person Tom("tom", 21);
	std::cout << square(Tom) << std::endl;
	birthday(Tom);
	std::cout << square(Tom) << std::endl;
	return 0;
}

int square(const Person & person)
{
	int buff = person.Age();
	return buff*buff;
}
void birthday(Person & person)
{
	++person.Age();
}
