#ifndef STACK_H
#define STACK_H

template<typename T>
class List
{
	template<typename T>
	class Node
	{
		T value;
		Node<T> * next;
	};

	Node<T> * head;
	Node<T> * tail;

	void Clear (Node<T> *);

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
};


void push_op(op_list *, char);
void pop_op(op_list *);

int empty_op(op_list *);
char top_op(op_list *);

#endif //STACK_H
