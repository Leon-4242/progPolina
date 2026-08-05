#include "stack.h"

/* --- Стек чисел (list) --- */

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

/* Вставить curr сразу после parent в списке */
void add_node(node * parent, node * curr)
{
	curr->next = parent->next;
	parent->next = curr;
}

/* Отцепить и вернуть элемент, следующий за parent */
node * del_node(node * parent)
{
	if (parent->next == NULL)
	{
		return NULL;
	}

	node * curr;
	curr = parent->next;
	parent->next = curr->next;
	curr->next = NULL;

	return curr;
}

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

/* Push: новый элемент становится tail — вершиной стека */
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

/* Pop: удаляем tail — верхний элемент стека */
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

	/* Ищем предпоследний узел, отцепляем tail */
	node * curr = lst->head;
	while (curr->next != lst->tail)
	{
		curr = curr->next;
	}

	delete_node(del_node(curr));
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

/* --- Стек операторов (op_list) — та же логика, другой тип данных --- */

op_node * make_op_node(char val)
{
	op_node * buff = (op_node *)malloc(sizeof(op_node));
	buff->value = val;
	buff->next = NULL;

	return buff;
}

void delete_op_node(op_node * curr)
{
	free(curr);
}

void add_op_node(op_node * parent, op_node * curr)
{
	curr->next = parent->next;
	parent->next = curr;
}

op_node * del_op_node(op_node * parent)
{
	if (parent->next == NULL)
	{
		return NULL;
	}

	op_node * curr = parent->next;
	parent->next = curr->next;
	curr->next = NULL;

	return curr;
}

op_list * make_op_list(void)
{
	op_list * buff = (op_list *)malloc(sizeof(op_list));
	buff->head = NULL;
	buff->tail = NULL;

	return buff;
}

void del_op_list(op_list * lst)
{
	while (lst->head)
	{
		pop_op(lst);
	}
	free(lst);
}

void push_op(op_list * lst, char value)
{
	op_node * buff = make_op_node(value);
	if (lst->tail == NULL)
	{
		lst->head = buff;
	}
	else
	{
		add_op_node(lst->tail, buff);
	}

	lst->tail = buff;
}

void pop_op(op_list * lst)
{
	if (!lst->head)
	{
		return;
	}

	if (lst->head == lst->tail)
	{
		delete_op_node(lst->tail);
		lst->head = lst->tail = NULL;
		return;
	}

	op_node * curr = lst->head;
	while (curr->next != lst->tail)
	{
		curr = curr->next;
	}

	delete_op_node(del_op_node(curr));
	lst->tail = curr;
}

int empty_op(op_list * lst)
{
	return !lst->head;
}

char top_op(op_list * lst)
{
	return lst->tail->value;
}
