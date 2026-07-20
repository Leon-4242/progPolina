#include <stdio.h>
#include <math.h>

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



int data_check (operation *number, double *a, double *b)
{
    int buff = 0;

        printf("Enter the operation number: addition - 1, subtraction - 2, multiplication - 3, division - 4\n");
        scanf("%d", &buff);

		if(buff < 1 || buff > 4)
        {
             printf("Incorrect operation number\n");
			 return 1;
        }

			*number = buff;
	
        printf("Enter two numbers:\n");
        scanf("%lf %lf", a, b);

		if (*number == DIV && fabs(*b) < 1e-15)
		{
			printf("Division by zero\n");
			return 2;
		}
    return 0;
}

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
    return NULL;
    }
    
}

double sum(double a, double b)
{
	return a+b;
}

double sub(double a, double b)
{
	return a-b;
}
double mul(double a , double b)
{
    return a*b;
}
double div(double a, double b)
{
    return a/b;
}
