#include <stdio.h>
#include <malloc.h>

typedef struct NODE
{
	double value;
	struct NODE * next;
} node;

node * make_node(double);
void delete_node(node *);

void add_node(node *, node *);
node * del_node(node *, node *);


int main(void)
{
	node * head = make_node(0);
	delete_node(head);
	return 0;
}

node * make_node(double val)
{
	node * buff;
	buff = (node *)malloc(sizeof(node));
	buff->value = val;
	buff->next = NULL;
	
	return buff;
}

void delete_node(node * curr)
{
	free(curr);
}

void add_node(node * parent, node * curr)
{
	// if (parent->next == NULL)
//	if (!parent->next)
//	{
//		parent->next = curr;
//	}
//	else 
//	{
//		curr->next = parent->next;
//		parent->next = curr;
//	}

	curr->next = parent->next;
	parent->next = curr;
}

node * del_node(node * parent, node * curr)
{
    if(curr == NULL)
    {
        return NULL;
    }
        parent->next = curr->next;
        curr->next = NULL;
    
        return curr;
}
//TODO: удалить ноду
// parent->curr->buff
// если curr == NULL, то ничего не делает
// если curr != NULL, то parent->buff, а функция вернёт curr
