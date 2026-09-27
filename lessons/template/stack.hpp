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
		Node(const T& val, Node * ptr = nullptr):
			value(val), next(ptr)
		{
		}
	};

	Node * head;
	int Size;

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
		Size = 0
	}

	void clear()
	{
		this->Clear(head);
		head = nullptr;
		Size = 0;
	}

	~List()
	{
		this->clear();
	}

    void push(T val)
	{
		Node * buff = new Node(val, head);
		buff->value = val;
		buff->next =  head;
		head = buff;
		++Size;
	}

	bool pop()
	{
		if (Size == 0)
		{
			return false;
		}
		--Size;
		/*
		if (!head)
		{
			return false;
		}
		*/
		Node * curr = head;
		head = head->next;
		delete curr;
		return true;
	}

	bool empty() const
	{
		return head == nullptr;
	}

	int size() const
	{
		return Size;
	}

	T top() const
	{
		if (empty())
		{
			return T();
		}
		return head->value;
	}

	List<T> operator+ (const List<T>& val) const
	{
		//Соединение двух списков
		return List<T>();
	}
};



#endif //STACK_H
