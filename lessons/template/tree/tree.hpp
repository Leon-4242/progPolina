#ifndef TREE_H
#define TREE_H

#include <stdexcept>
#include <cstddef> 
#include <utility>

//TODO:
//  std::size_t size () const;
//  bool empty () const;
//Добавить reverse begin; reverse end;(+новые итераторы)            
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

		Node(const K& k, const V& val, Node* left, Node* right, Node* parent);
		~Node();

		const K& key() const;
		void setKey(const K& k);
		
		V& value();
		const V & value() const;
 		bool operator < (const Node& other) const;
	};

	public: // добавлено: итератор должен быть виден снаружи
	class iterator
	{
		Node * curr;
		std::size_t k;
		const Tree * origin; // изменено: было Tree *

		public:
		iterator(Node * n, std::size_t k, const Tree * orig);
		iterator & operator++ ();
		iterator & operator-- ();
		bool operator == (const iterator & it) const;
		bool operator != (const iterator & it) const;
		
		std::pair<const K &, V &> operator* ();
	};
	class reverse_iterator
	{
		//TODO
		.
	};
	
	public:
	Tree();
	~Tree();

	Tree(const Tree & t);
	Tree & operator= (const Tree & t);
	Tree(Tree && t);
	Tree & operator= (Tree && t);

	iterator begin() const;
	iterator end() const;

    void clear();
    bool push(const K& key, const V& val);
    bool find(const K& key) const;
	bool search(const K& key, V& value) const;
	V& at (const K& key);
	V at (const K& key) const;
	V& operator[] (const K& key);
	bool remove (const K& key);
	void map(V (*f)(const K&));
	std::size_t size() const;
	bool empty() const;

	private:
	//data
	Node* root;
	std::size_t size;

	//static methods
	static void clearNodeRec(Node* curr);
    static Node* push(Node* curr, Node* parent, const K& key, const V& val);
	static const Node * find_example(const Node * curr, const K& key);	
	static Node * find_example(Node * curr, const K& key);	
	static void map_rec(Node * curr, V (*manipulation)(const K&));
	static void copy_rec(Node * parent, Node ** curr, Node * src);

	//iterative methods
	void clearNodeIter(Node *);

	//additional
	void clearNode(Node* curr)
    {
		Tree::clearNodeRec(curr);
	}
	void remove_rec(Node* curr, const K& key);

};

#include "tree_main.hpp"

#include "tree_node.hpp"
#include "tree_iterator.hpp"

#include "tree_rec.hpp"
#include "tree_iter.hpp"

#endif //TREE_H
