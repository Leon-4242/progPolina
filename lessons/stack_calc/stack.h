#ifndef STACK_H
#define STACK_H

#include <malloc.h>

/* Узел стека чисел: значение и ссылка на следующий элемент */
typedef struct NODE
{
	double value;
	struct NODE * next;
} node;

node * make_node(double);
void delete_node(node *);

void add_node(node *, node *);
node * del_node(node *);

/* Стек на связном списке: head — начало, tail — вершина (откуда push/pop) */
typedef struct LIST
{
	node * head;
	node * tail;
} list;

list * make_list(void);
void del_list(list *);
void push_back(list *, double);  /* положить на вершину */
void pop_back(list *);           /* снять с вершины */

int empty(list *);
double value(list *);            /* посмотреть верхний элемент */

/* То же самое, но для операторов (+, -, *, /, скобки) */
typedef struct OP_NODE
{
	char value;
	struct OP_NODE * next;
} op_node;

typedef struct OP_LIST
{
	op_node * head;
	op_node * tail;
} op_list;

op_list * make_op_list(void);
void del_op_list(op_list *);
void push_op(op_list *, char);
void pop_op(op_list *);

int empty_op(op_list *);
char top_op(op_list *);

#endif
