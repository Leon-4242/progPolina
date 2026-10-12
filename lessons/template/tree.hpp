#ifndef TREE_H
#define TREE_H

//TODO:
//1) bool Tree<K, V>::find(const K&)
//2) V&/V Tree<K, V>::operator[] (const K&) /const
//3) void Tree<K, V>::remove(const K&)
//4*) void Tree<K, V>::map(V (*f)(const K&)) 

template<typename K, typename V>
class Tree
{
	class Node
	{
		K Key;
		V Value;
		public:

		Node * left, * right;

		Node(const K& k, const V& val, Node* left, Node* right):
			Key(k), Value(val), left(left), right(right)
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

 	void clearNode(Node* curr)
    {
        if (curr == nullptr) 
        {
            return;
        }
        
        clearNode(curr->left);
        clearNode(curr->right);
        delete curr;
    }

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
};

#endif //TREE_H
