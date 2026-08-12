#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>
#include <iostream>

#define N 100000

class Person
{
	std::string name;
	int age;
//	int * cards;

	public:
	Person(std::string name, int age): 
		name(name),
		age(age)
	{
//		cards = new int[36];
//		std::cout << "person created: " + name + "\n";
	}

	~Person()
	{
//		delete[] cards;
//		std::cout << "person deleted: " + name + "\n";
	}

/*
	int getAge() const
	{
		return age;
	}

	void setAge(int Age)
	{
		age = Age;
	}
*/

	int Age() const
	{
		return age;
	}

	int & Age()
	{
		return age;
	}

	Person & operator= (const Person & person)
	{
		age = person.age;
		name = person.name;
		return *this;
	}

	Person(const Person & person):
		age(person.age),
		name(person.name)
	{
	}

	Person operator+ (const Person & person) const
	{
		return Person(name + "-" + person.name, age + person.age);
	}
};

#endif //BASECLASS_H
