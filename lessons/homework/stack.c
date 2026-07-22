#include <stdio.h>
#include <malloc.h>

typedef struct NODE
{
	double value;
	struct NODE * next;
} node;

node * make_node(double);
void del_node(node *);

void add_node(node *, node *);


int main(void)
{
	node * head = make_node(0);
	del_node(head);
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

void del_node(node * curr)
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

//TODO: удалить ноду
// parent->curr->buff
// если curr == NULL, то ничего не делает
// если curr != NULL, то parent->buff, а функция вернёт curr
