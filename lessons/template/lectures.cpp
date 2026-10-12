	auto buff = tree.search(2);

	
	if (buff == std::null_opt)
	{
		std::cout << "Not found" << std::endl;
	}
	else
	{
		std::cout << *buff << std::endl;
	}
	

	std::vector<int> arr(5);

	arr[5] = 2;
	try 
	{
		arr.at(5) = 2;
	}
	catch (const std::out_of_range& err)
	{
		std::cout << err.what() << std::endl;
	}

int div() //бросает исключение при делении на 0
int algo() //вызывает функцию div()
int main() //вызывает algo()
		   //

	std::optinal<V> search_opt(Node* curr, const K& key)
	{
		if (curr == nullptr)
		{
			return std::null_opt;
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
			return std::optinal<V>(curr->value());
		}
	}

