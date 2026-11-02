template<typename K, typename V>
void Tree<K, V>::clearNodeRec(Tree<K, V>::Node * curr)
{
    if (curr == nullptr) 
    {
        return;
    }
        
    clearNodeRec(curr->left);
    clearNodeRec(curr->right);
	delete curr;
}

template<typename K, typename V>
Tree<K, V>::Node* Tree<K, V>::push(Tree<K, V>::Node* curr, Tree<K, V>::Node* parent, const K& key, const V& val)
{
	if (curr == nullptr) 
    {
        return new Node(key, val, nullptr, nullptr, parent);
    }

    if (key < curr->key()) 
    {
        curr->left = push(curr->left, curr, key, val);
    } 
    else if (curr->key() < key) 
    {
        curr->right = push(curr->right, curr, key, val);
    }
    else 
    {
        curr->value() = val;
    }

    return curr;
}

template<typename K, typename V>
const Tree<K, V>::Node * Tree<K, V>::find_example(const Tree<K, V>::Node * curr, const K& key) 
{
	if (curr == nullptr)
	{
		return nullptr;
	}

    if (key < curr->key()) 
    {
        return find_example(curr->left, key);
    } 
        
	if (curr->key() < key) 
    {
        return find_example(curr->right, key);
    }
        
	return curr;
}

template<typename K, typename V>
Tree<K, V>::Node * Tree<K, V>::find_example(Tree<K, V>::Node * curr, const K& key) 
{
	if (curr == nullptr)
	{
		return nullptr;
	}

    if (key < curr->key()) 
    {
        return find_example(curr->left, key);
    } 
        
	if (curr->key() < key) 
    {
        return find_example(curr->right, key);
    }
        
	return curr;
}

template<typename K, typename V>	
void Tree<K, V>::map_rec(Tree<K, V>::Node * curr, V (*manipulation)(const K&))
{
	if (curr == nullptr)
	{
		return;
	}

	map_rec(curr->left, manipulation);
	curr->value() = manipulation(curr->key());
	map_rec(curr->right, manipulation);
}

template<typename K, typename V>
void Tree<K, V>::copy_rec(Tree<K, V>::Node * parent, Tree<K, V>::Node ** curr, Tree<K, V>::Node * src)
{
	if (!src)
	{
		return;
	}
	
	*curr = new Node (src->key(), src->value(), nullptr, nullptr, parent);
	copy_rec(curr, &(curr->left), src->left);
	copy_rec(curr, &(curr->right), src->right);
}
