#ifndef STACK_H
#define STACK_H


template<typename T>
class List
{
	class Node
	{
        public:
		T value;
		Node * next;
	};

	Node * head;
	Node * tail;

	void Clear (Node * );

	public:
	List()
	{
		head = tail = nullptr;
	}

	void clear()
	{
		this->Clear(head);
	}

	~List()
	{
		this->clear();
	}

    void push(T val);
bool pop();

bool empty() const;
T top() const;
};


#include "stack.cpp"

#endif //STACK_H