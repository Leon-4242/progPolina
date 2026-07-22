#include <stdio.h>
#include <math.h>

#include <assert.h>

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

int main (void)
{
	func f;
	while (1)
    {
		operation number = SUM;
        double a = 0, b = 0, result = 0;
        if (data_check (&number, &a, &b) != 0)
        {
            continue;
        }
		f = function(number);
		result = f(a, b);
		printf("result = %lf\n", result);

    }
    
    return 0;
}



int data_check (operation * number, double * a, double * b)
{
	char op = 0;

	printf("Enter expresion:\n");
	scanf(" %lf %c %lf", a, &op, b);

	if (op != '+' && op != '-' && op != '*' && op != '/')
	{
		printf("I don't know this operation :(.\n");
		return 1;
	}

//TODO: переписать if else в switch, в отдельной функции

	if (op == '+') 
	{
		*number = SUM;
	} 
	else if (op == '-')
	{
		*number = SUB;
	} 
	else if (op == '*')
	{
		*number = MUL;
	} 
	else if (op == '/')
	{
		*number = DIV;
	}

	if (*number == DIV && fabs(*b) < 1e-15)
	{
		printf("Division by zero\n");
		return 2;
	}

	return 0;
}

//3+8*7-1
//3 8 7 * + 1 -
//
// array [1, 2, 5, 9, 3, 7]
// list (1)->(2)->(5)->(9)->(3)->(7)
//
// list (1)<->(2)<->(5)<->(9)<->(3)<->(7)
//
// list (1)->(2)->(5)->(6)->(9)->(3)->(7)

// list (3+8*7-1)



func function (operation number)
{

    switch (number)
    {
    case SUM:
    return sum;

    case SUB:
    return sub;

    case MUL:
    return mul;

    case DIV:
    return div;

    default:  
    assert(0);
    }

	return NULL;
}

double sum(double a, double b)
{
	return a+b;
}

double sub(double a, double b)
{
	return a-b;
}
double mul(double a, double b)
{
    return a*b;
}
double div(double a, double b)
{
    return a/b;
}
