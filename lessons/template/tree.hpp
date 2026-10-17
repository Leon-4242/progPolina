#ifndef TREE_H
#define TREE_H

//TODO:
//1) bool Tree<K, V>::find(const K&)                -
//2) V&/V Tree<K, V>::operator[] (const K&) /const	-
//3) void Tree<K, V>::remove(const K&)              +
//4*) void Tree<K, V>::map(V (*f)(const K&))        -

template<typename K, typename V>
class Tree
{
	class Node
	{
		K Key;
		V Value;
		public:

		Node * left, * right;
		Node * parent;

		Node(const K& k, const V& val, Node* left, Node* right, Node* parent):
			Key(k), Value(val), left(left), right(right), parent(parent)
		{
		}
		~Node()
		{
		}

		K key() const
		{
			return Key;
		}
		
		V& value()
		{
			return Value;
		}
		V value() const
		{
			return Value;
		}

 		bool operator < (const Node& other) const
        {
            return Key < other.Key;
        }
	};

	void clearNodeRec(Node* curr)
	{
        if (curr == nullptr) 
        {
            return;
        }
        
        clearNode(curr->left);
        clearNode(curr->right);
        delete curr;
	}

	void clearNodeIter(Node *)
	{
		bool left = true;
		Node * curr = root;
		while (curr)
		{
			if (curr->left)
			{
				//stack.push(curr);
				prev = curr;
				left = true;
				curr = curr->left;
				continue;
			}
			if (curr->right)
			{
				//stack.push(curr);
				prev = curr;
				left = false;
				curr = curr->right;
				continue;
			}

			//curr = curr->prev;
			//delete (left ? curr->left : curr->right);
			
			delete curr;
			// curr = stack.pop();

			if (left)
			{
				prev->left = nullptr;
			}
			else
			{
				prev->right = nullptr;
			}
			curr = root;
		}
	}

 	void clearNode(Node* curr)
    {
		clearNodeRec(curr);
	}

	//TODO: согласовать с curr->parent
    Node* push(Node* curr, const K& key, const V& val)
    {
        if (curr == nullptr) 
        {
            return new Node(key, val, nullptr, nullptr);
        }

        if (key < curr->key()) 
        {
            curr->left = push(curr->left, key, val);
        } 
        else if (curr->key() < key) 
        {
            curr->right = push(curr->right, key, val);
        }
        else 
        {
            curr->value() = val;
        }

        return curr;
    }

	bool search(Node* curr, const K& key, V& value)
	{
		if (curr == nullptr)
		{
			return false;
		}

        if (key < curr->key()) 
        {
            return search(curr->left, key, value);
        } 
        else if (curr->key() < key) 
        {
            return search(curr->right, key, value);
        }
        else 
        {
			value = curr->value();
			return true;
		}
	}

	V& search_SEGFAULT(Node* curr, const K& key)
	{
        if (key < curr->key()) 
        {
            return search_SEGFAULT(curr->left, key);
        } 
        else if (curr->key() < key) 
        {
            return search_SEGFAULT(curr->right, key);
        }
        else 
        {
			return curr->value();
		}
	}

	V search_SEGFAULT(Node* curr, const K& key) const
	{
        if (key < curr->key()) 
        {
            return search_SEGFAULT(curr->left, key);
        } 
        else if (curr->key() < key) 
        {
            return search_SEGFAULT(curr->right, key);
        }
        else 
        {
			return curr->value();
		}
	}


	void remove_rec(Node* curr, const K& key) const
	{
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

		if (buff == root)
		{
			root = nullptr;
			delete buff;
		}

		if (buff != curr)
		{
			curr->Key() = buff->Key();
			curr->Value() = buff->Value();
			legacy = buff->right;
		}
		else 
		{
			legacy = buff->left;
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

	Node* root;
	public:
	Tree():
		root(nullptr)
	{
	}

	~Tree()
	{
		this->clear();
	}

    void clear()
    {
        clearNode(root);
        root = nullptr;
    }

    void push(const K& key, const V& val)
    {
        root = push(root, key, val);
    }

	bool search(const K& key, V& value)
	{
		return search(root, key, value);
	}

	V& operator[] (const K& key)
	{
		return search_SEGFAULT(root, key);
	}

	V operator[] (const K& key) const
	{
		return search_SEGFAULT(root, key);
	}

	void remove (const K& key) 
	{
		return remove_rec(root, key);
	}
};

#endif //TREE_H
