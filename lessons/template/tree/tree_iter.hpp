template <typename K, typename V>
void Tree<K, V>::clearNodeIter(Tree<K, V>::Node *)
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
