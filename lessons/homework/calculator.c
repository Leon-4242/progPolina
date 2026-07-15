#include <stdio.h>
#include <math.h>
//TODO::1)написать функцию, котрая получает данные, проверяет корректность и возвращает код ошибки, если она есть.
//		2)написать функцию, котрая получает перечисление, а возвращает указатель на функцию
//		3)доделать нужные функция, почистить код
//		4)Опционально: возрващаемое значение первой функции (функции ввода), можно тоже сделать перечислением
//T func_name(T1, T2, ..., Tk);

//T func_name(T1 arg1, T2 arg2, ..., Tk argk)
//{
//
//}

//typedef T (*func)(T1, T2, ..., Tk);
typedef double (*func)(double, double);

double sum(double, double);
double sub(double, double);
double mult(double, double);
double div(double, double);

typedef enum OPERATION 
{
	SUM //0
	SUB //1
	MULT //2
	DIV //3
} operation;

/*... (double * a, double *b)
{
	scanf("%lf %lf", a, b);
	*number = buff-1;
}
*/

int main (void)
{
//	int (*sum)(int, int);
	func f;
	while (1)
    {
		int buff = 0;
        //enum OPERATION
		operation number = SUM;
        double a = 0, b = 0, result = 0;
//		func(&a, &b, &number);

        printf("Enter the operation number: addition - 1, subtraction - 2, multiplication - 3, division - 4\n");
        scanf("%d", &buff);

		//if (buff not in enum OPERATION)
		if(buff < 1 || buff > 4)
        {
             printf("Incorrect operation number\n");
			 continue;
        }

		{
			number = buff-1;
		}

        printf("Enter two numbers:\n");
        scanf("%lf %lf", &a, &b);

		if (number == DIV && fabs(b) < 1e-15)
		{
			printf("Division by zero\n");
			continue;
		}

		switch (number)
		{
			case SUM:
			{
//				result = sum(a, b);
				f = sum;
				break;
			}
			case SUB:
			{
//				result = sub(a, b);
				f = sub;
				break;
			}
			case MULT:
			{
//				result = mult(a, b);
				f = mult;
				break;
			}
			case DIV:
			{
//				result = div(a, b);
				f = div;
				break;
			}
		}

		result = f(a, b);

		printf("result = %lf\n", result);

/*        if (number == 1)
        {
            result = a + b;
            printf("result = %lf\n", result);
        }
        
        else if (number == 2)
        {
            result = a - b;
            printf("result = %lf\n", result);
        }

        else if (number == 3)
        {
            result = a * b;
            printf("result = %lf\n", result);
        }

        else if (number == 4)
        {
            if (b == 0)
            {
                printf("Division by zero\n");
                continue;
            }

            result = a / b;
            printf("result = %lf\n", result);
        }
*/
    }
    
    return 0;
}

double sum(double a, double b)
{
	return a+b;
}

double sub(double a, double b)
{
	return a-b;
}
double mult(double, double);
double div(double, double);
//TODO: other
