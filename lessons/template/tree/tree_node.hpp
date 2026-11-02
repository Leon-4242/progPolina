template <typename K, typename V>
Tree<K, V>::Node::Node(const K& k, const V& val, Node* left, Node* right, Node* parent):
	Key(k), Value(val), left(left), right(right), parent(parent)
{
}

template <typename K, typename V>
Tree<K, V>::Node::~Node()
{
}

template <typename K, typename V>
const K& Tree<K, V>::Node::key() const // изменено: было K key() const (возвращало копию, итератор брал на неё ссылку)
{
	return Key;
}

// добавлено: чтобы remove_rec мог поменять ключ
template <typename K, typename V>
void Tree<K, V>::Node::setKey(const K& k)
{
	Key = k;
}
				
template <typename K, typename V>
V& Tree<K, V>::Node::value()
{
	return Value;
}
		
template <typename K, typename V>
const V& Tree<K, V>::Node::value() const
{
	return Value;
}

 		
template <typename K, typename V>
bool Tree<K, V>::Node::operator < (const Node& other) const
{
	return Key < other.Key;
}
