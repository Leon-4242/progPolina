#ifndef PERSON_H
#define PERSON_H

class Student;

class Person
{
	friend class Student;

	protected:
	std::string name;
	int age;
	
	public:
	Person(std::string n, int a):
		name(n), age(a)
	{
	}

	void say() const
	{
		std::cout << "Hello! I'm " + name << std::endl;	
	}

	void goodbye() const
	{
		std::cout << "goodbye!" << std::endl; 
	}
};

class Student: public Person
{
	int id;

	public:
	Student(std::string n, int a, int id):
		Person(n, a), id(id)
	{
	}

	void say() const
	{
		std::cout << "Hello! I'm " + name  + ", from MSU."<< std::endl;	
	}
}

#endif //PERSON_H
	   //
	   //

int main(void)
{
	Person Tom("tom", 23);
	Student Bob("bob", 24, 1234);

	Tom.say();
	Bob.say();

	Tom.goodbye();
	Bob.goodbye();
}
