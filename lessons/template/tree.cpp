#ifndef TREE_H
#define TREE_H

template<typename K, typename V>
class Tree
{
    class Node
    {
    public:
        K Key;
        V Value;
        Node* left;
        Node* right;

        // ИСПРАВЛЕНО: добавлено двоеточие перед списком инициализации
        Node(K k, V val, Node* left, Node* right) :
            Key(k), Value(val), left(left), right(right)
        {
        }
        
        ~Node() 
        {
        }

        bool operator < (const Node& other) const
        {
            return Key < other.Key;
        }
    };

    Node* root;

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

    Node* push(Node* curr, K key, V val)
    {
        if (curr == nullptr) {
            return new Node(key, val, nullptr, nullptr);
        }

        if (key < curr->Key) 
        {
            curr->left = push(curr->left, key, val);
        } 
        else if (curr->Key < key) 
        {
            curr->right = push(curr->right, key, val);
        }
        else {
            curr->Value = val;
        }

        return curr;
    }

public:
    Tree()
    {
        root = nullptr;
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

    void push(K key, V val)
    {
        root = push(root, key, val);
    }
}; 

#endif // TREE_H