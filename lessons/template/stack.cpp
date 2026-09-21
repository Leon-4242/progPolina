

template<typename T>
void List<T>::Clear(Node * node)
{
	while (node != nullptr)
	{
		Node * next_node = node->next;
		delete node;
		node = next_node;
	}
}

template<typename T>
void List<T>::push(T val)
{
	Node * buff = new Node;
	buff->value = val;
	buff->next = nullptr;

	if (tail == nullptr)
	{
		head = tail = buff;
	}
	else
	{
		tail->next = buff;
		tail = buff;
	}
}

// если void, то throw
template<typename T>
bool List<T>::pop()
{
	if (!head)
	{
		return false;
	}

	if (head == tail)
	{
		delete tail;
		head = tail = nullptr;
		return true;
	}

	Node * curr = head;
	while (curr->next != tail)
	{
		curr = curr->next;
	}

	delete tail;
	tail = curr;
	tail->next = nullptr;
	return true;
}

template<typename T>
bool List<T>::empty() const
{
	return head == nullptr;
}

template<typename T>
T List<T>::top() const
{
	if (empty())
	{
		return T();// если пустой стек не возвращаем значение нулевого указателя???
	}
	return tail->value;
}