#include "stack.h"

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
	curr->next = parent->next;
	parent->next = curr;
}

node * del_node(node * parent)
{
    if(parent->next == NULL)
    {
        return NULL;
    }
		node * curr;
		curr = parent->next;
        parent->next = curr->next;
        curr->next = NULL;
    
        return curr;
}
//TODO: убрать из аргументов curr
// parent->curr->buff
// если curr == NULL, то ничего не делает
// если curr != NULL, то parent->buff, а функция вернёт curr
//

list * make_list(void)
{
	list * buff = (list *)malloc(sizeof(list));
	buff->head = NULL;
	buff->tail = NULL;

	return buff;
}

void del_list(list * lst)
{
	while (lst->head)
	{
		pop_back(lst);
	}
	free(lst);
}

void push_back(list * lst, double value)
{
	node * buff = make_node(value);
	if (lst->tail == NULL)
	{
		lst->head = buff;
	}
	else 
	{
		add_node(lst->tail, buff);
	}

	lst->tail = buff;
}

void pop_back(list * lst)
{
	if (!lst->head)
	{
		return;
	}

	if (lst->head == lst->tail)
	{
		delete_node(lst->tail);
		lst->head = lst->tail = NULL;
		return;
	}

	node * curr = lst->head;
	while (curr->next != lst->tail)
	{
		curr = curr->next;
	}

	delete_node(del_node(curr, lst->tail));
	lst->tail = curr;
}

int empty(list *lst)
{
	return ! lst->head;
}

double value(list * lst)
{
	return lst->tail->value;
}
