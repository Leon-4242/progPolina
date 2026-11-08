template<typename K, typename V>
Tree<K, V>::Tree():
	root(nullptr), size(0)
{
}

template<typename K, typename V>
Tree<K, V>::~Tree()
{
	this->clear();
	root = nullptr;
	size = 0;
}

template<typename K, typename V>
Tree<K, V>::Tree(const Tree<K, V> & t)
{
	if (!t.root)
	{
		root = nullptr;
		size = 0;
	}
	else
	{
		copy_rec(nullptr, &root, t.root);
		size = t.size;
	}
}

template<typename K, typename V>
Tree<K, V> & Tree<K, V>::operator= (const Tree<K, V> & t)
{
	if (this != &t)
	{
		this->clear();

		root = nullptr;
		copy_rec(nullptr, &root, t.root);
		size = t.size;
	}
	return *this;
}


template<typename K, typename V>
Tree<K, V>::Tree(Tree<K, V> && t)
{
	root = t.root;
	t.root = nullptr;

	size = t.size;
	t.size = 0;
}

template<typename K, typename V>
Tree<K, V> & Tree<K, V>::operator= (Tree<K, V> && t)
{
	if (this != &t)
	{
		this->clear();

		root = t.root;
		t.root = nullptr;

		size = t.size;
		t.size = 0;
	}
	return *this;
}

template<typename K, typename V>
void Tree<K, V>::clear()
{
	clearNode(root);
    root = nullptr;
	size = 0;
}

template<typename K, typename V>
bool Tree<K, V>::push(const K& key, const V& val)
{
	if(find(key))
	{
		at(key) = val;
		return false;
	}
    root = push(root, nullptr, key, val);
	++size;
	return true;
}

template<typename K, typename V>
bool Tree<K, V>::find(const K& key) const 
{
	return find_example(root, key) != nullptr;
}

template<typename K, typename V>
bool Tree<K, V>::search(const K& key, V& value) const 
{
	Node * buff = find_example(root, key);
	if (buff != nullptr)
	{
		value = buff->value();
		return true;
	}
	return false;
}

template<typename K, typename V>
V& Tree<K, V>::at (const K& key)
{
	Node * buff = find_example(root, key);
	if (buff != nullptr)
	{
		return buff->value();
	}
	else
    {
	    throw std::out_of_range("key not found");
    }
}

template<typename K, typename V>
V Tree<K, V>::at (const K& key) const
{
	Node * buff = find_example(root, key);
	if (buff != nullptr)
	{
		return buff->value();
	}
	else
    {
        throw std::out_of_range("key not found");
    }
}

template<typename K, typename V>
V& Tree<K, V>::operator[] (const K& key)
{
	Node * buff = find_example(root, key);
	if (buff == nullptr)
	{
		push(key, V());
		buff = find_example(root, key);
	}

	return buff->value();
}

template<typename K, typename V>
bool Tree<K, V>::remove (const K& key)
{
	if(!find(key))
	{
		return false;
	}
	remove_rec(root, key);
	--size;
	return  true;
}

template<typename K, typename V>
void Tree<K, V>::map(V (*f)(const K&))
{
	map_rec(root, f);
}


template<typename K, typename V>
void Tree<K, V>::remove_rec(Tree<K, V>::Node* curr, const K& key) 
{
	if(curr == nullptr)
    {
        return;
    }
	if (key < curr->key()) 
    {
        remove_rec(curr->left, key);
		return;
	}
	if (curr->key() < key) 
    {
        remove_rec(curr->right, key);
		return;
    }
			
	Node * buff = curr, * legacy = nullptr; 
	if (buff->right)
	{
		buff = buff->right;
		while (buff->left)
		{
			buff = buff->left;
		}
	}

	if (buff != curr)
	{
		curr->setKey(buff->key()); // изменено: было curr->Key = buff->Key;
		curr->value() = buff->value(); // изменено: было curr->Value = buff->Value;
		legacy = buff->right;
	}
	else 
	{
		legacy = buff->left;
	}
        
	if (legacy)
    {
        legacy->parent = buff->parent;
    }

    if (buff == root)
	{
		root = legacy;
		delete buff;
        return;
	}

	if (buff->parent->left == buff)
	{
		buff->parent->left = legacy;
		delete buff;
	}
	else
	{
		buff->parent->right = legacy;
		delete buff;
	}
}
template<typename K, typename V>
std::size_t Tree<K, V>::size() const
{
	return size;
}

template<typename K, typename V>
bool Tree<K, V>::empty() const
{
	if (size == 0)
		return true;
	else
		return false;
}

