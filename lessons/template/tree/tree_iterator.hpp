template <typename K, typename V>
Tree<K, V>::base_iterator::base_iterator(Tree<K, V>::Node * n, std::size_t k, const Tree<K, V> * orig): // изменено: const Tree *
	curr(n),k(k),origin(orig)
{
}

template <typename K, typename V>
Tree<K, V>::base_iterator & Tree<K, V>::base_iterator::move_right ()
{
	if (curr == nullptr)
	{
		return *this;
	}

	if (curr->right != nullptr)
	{
		curr = curr->right;
		while (curr->left)
		{
			curr = curr->left;
		}
	}
	else
	{
		while (curr->parent != nullptr && curr->parent->right == curr)
		{
			curr = curr->parent;
		}
		curr = curr->parent;
	}
	++k;
	return *this;
}

template <typename K, typename V>
Tree<K, V>::base_iterator & Tree<K, V>::base_iterator::move_left ()
{
	if (curr == nullptr)
	{
		curr = origin->root;
		while (curr && curr->right)
		{
			curr = curr->right;
		}
		--k;
		return *this;
	}
	if (curr->left != nullptr)
	{
		curr = curr->left;
		while (curr->right)
		{
			curr = curr->right;
		}
	}
	else
	{
		while (curr->parent != nullptr && curr->parent->left == curr)
		{
			curr = curr->parent;
		}
		curr = curr->parent;
	}
	--k;
	return *this;
}
	
template <typename K, typename V>
std::pair<const K &, V &> Tree<K, V>::base_iterator::operator* ()
{
	return std::pair<const K &, V &> (curr->key(), curr->value());
}

template <typename K, typename V>
bool Tree<K, V>::base_iterator::operator == (const Tree<K, V>::base_iterator & it) const
{
	return origin==it.origin && k == it.k;
}

template <typename K, typename V>
bool Tree<K, V>::base_iterator::operator != (const Tree<K, V>::base_iterator & it) const
{
	return !(it == *this);
}

template<typename K, typename V>
Tree<K, V>::iterator Tree<K, V>::begin() const
{
	Node * curr = root;
	while (curr && curr->left)
	{
		curr = curr->left;
	}

	return iterator(curr, 0, this);
}

template<typename K, typename V>
Tree<K, V>::iterator Tree<K, V>::end() const
{
	return iterator(nullptr, tree_size, this);
}	

template<typename K, typename V>
Tree<K, V>::reverse_iterator Tree<K, V>::rbegin() const
{
	return reverse_iterator(nullptr, tree_size, this);
}

template<typename K, typename V>
Tree<K, V>::reverse_iterator Tree<K, V>::rend() const
{
	Node * curr = root;
	while (curr && curr->left)
	{
		curr = curr->left;
	}

	return reverse_iterator(curr, 0, this);
}