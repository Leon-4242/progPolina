#ifndef TREE_H
#define TREE_H

template<typename K, typename V>
class Tree
{
	class Node
	{
		K Key;
		V Value;
		Node* left, right;
		public:
		Node(K k, V val, Node* left, Node* right):
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

//TODO:		bool operator <
//			Node a, b;
//			a < b <=> a.Key < b.Key 
	}

//TODO: CLEAR

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

/*
	push(K key, V val)
	{
		Node * add = new Node(key, val, nullptr, nullptr);
		
		Node * curr = root;
		if (*add < *curr)
		{
			curr = curr->left;
		}
		else if (*add > *curr)
		{
			curr = curr->right;
		}
	}
*/
}

#endif //TREE_H
