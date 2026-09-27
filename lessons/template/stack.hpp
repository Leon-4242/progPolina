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

	void Clear(Node * node)
	{
		while (node != nullptr)
		{
			Node * next_node = node->next;
			delete node;
			node = next_node;
		}
	}

	public:
	List()
	{
		head = nullptr;
	}

	void clear()
	{
		this->Clear(head);
		head = nullptr;
	}

	~List()
	{
		this->clear();
	}

    void push(T val)
	{
		Node * buff = new Node;
		buff->value = val;
		buff->next =  head;
		head = buff;

	}

	bool pop()
	{
		if (!head)
		{
			return false;
		}

		Node * curr = head;
		head = head->next;
		delete curr;
		return true;
	}

	bool empty() const
	{
		return head == nullptr;
	}

	T top() const
	{
		if (empty())
		{
			return T();
		}
		return head->value;
	}
};



#endif //STACK_H
