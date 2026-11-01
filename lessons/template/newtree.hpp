#ifndef TREE_H
#define TREE_H

#include <stdexcept>
#include <cstddef> 
#include <utility>

//TODO:
//Дописать итератор
//Согласовать логику size с нашими методами + 
//+ (возможно) изменить функции на возврат bool
//Добавить reverse begin; reverse end;
//Опционально: ещё const begin и const end;

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

		const K& key() const // изменено: было K key() const (возвращало копию, итератор брал на неё ссылку)
		{
			return Key;
		}

		// добавлено: чтобы remove_rec мог поменять ключ
		void setKey(const K& k)
		{
			Key = k;
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

	public: // добавлено: итератор должен быть виден снаружи
	class iterator
	{
		Node * curr;
		std::size_t k;
		const Tree * origin; // изменено: было Tree *

		public:
		iterator(Node * n, std::size_t k, const Tree * orig): // изменено: const Tree *
			curr(n),k(k),origin(orig)
			{
			}

		iterator & operator++ ()
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
		iterator & operator-- ()
		{
			if(curr == nullptr)
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
			
		std::pair<const K &, V &> operator* ()
		{
			return std::pair<const K &, V &> (curr->key(), curr->value());
		}
	};
	private: // добавлено: дальше снова закрытая часть

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
		Node * curr = root, * prev = nullptr;
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
			if(curr == root)
			{
				delete curr;
				root = nullptr;
				return;
			}
			
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
    Node* push(Node* curr, Node* parent, const K& key, const V& val)
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

	Node * find_example(Node * curr, const K& key) const 
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
	

	void remove_rec(Node* curr, const K& key) 
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

	void map_rec(Node * curr, V (*manipulation)(const K&))
	{
		if (curr == nullptr)
		{
			return;
		}

		map_rec(curr->left, manipulation);
		curr->value() = manipulation(curr->key());
		map_rec(curr->right, manipulation);
	}


	Node* root;
	std::size_t size;
	public:
	Tree():
		root(nullptr), size(0)
	{
	}

	~Tree()
	{
		this->clear();
	}

	// добавлено: запрет копирования (иначе два дерева удалят одни и те же узлы)
	Tree(const Tree &) = delete;
	Tree & operator= (const Tree &) = delete;

	iterator begin() const
	{
		Node * curr = root;
		while (curr && curr->left)
		{
			curr = curr->left;
		}

		return iterator(curr, 0, this);
	}
	
	iterator end() const
	{
		return iterator(nullptr, size, this);
	}

	iterator rbegin() const
	{
		Node * curr = root;
		while (curr && curr->right)
		{
			curr = curr->right;
		}

		return iterator(curr, size - 1, this);
	}

	iterator rend() const
	{
		return iterator(nullptr, (std::size_t) - 1, this);
	}



    void clear()
    {
        clearNode(root);
        root = nullptr;
		size = 0;
    }

    bool push(const K& key, const V& val)
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

    bool find(const K& key) const 
	{
		return find_example(root, key) != nullptr;
	}

	bool search(const K& key, V& value) const 
	{
		Node * buff = find_example(root, key);
		if (buff != nullptr)
		{
			value = buff->value();
			return true;
		}
		return false;
	}

	V& at (const K& key)
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
	
	V at (const K& key) const
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

 // две одинаковые функции 
	V& operator[] (const K& key)
	{
		Node * buff = find_example(root, key);
		if (buff == nullptr)
		{
			push(key, V());
			buff = find_example(root, key);
		}

		return buff->value();
	}

	V operator[] (const K& key) const
	{
		return at(key); // изменено: в const-дереве вставлять нельзя, поэтому как at (исключение, если ключа нет)
	}

	bool remove (const K& key)
	{
		if(!find(key))
		{
			return false;
		}
		remove_rec(root, key);
		--size;
		return  true;
	}

	void map(V (*f)(const K&))
	{
		map_rec(root, f);
	}
};

#endif //TREE_H
