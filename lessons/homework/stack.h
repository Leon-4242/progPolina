#ifndef STACK_H
#define STACK_H

#include <malloc.h>

#include <math.h>
#include <assert.h>

typedef struct NODE
{
	double value;
	struct NODE * next;
} node;

node * make_node(double);
void delete_node(node *);

void add_node(node *, node *);
node * del_node(node *);

typedef struct LIST
{
	node * head;
	node * tail;
} list;

list * make_list(void);
void del_list(list *);
void push_back(list *, double);
void pop_back(list *);

int empty(list *);
double value(list *);




typedef double (*func)(double, double);

double sum(double, double);
double sub(double, double);
double mul(double, double);
double div(double, double);

typedef enum OPERATION 
{
    SUM = 1, 
    SUB, 
    MUL, 
    DIV
} operation;

int data_check (operation *number, double *a, double *b);
func function (operation number);
operation function_op(char op);

#endif
