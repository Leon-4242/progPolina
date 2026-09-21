#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "stack.hpp"

#define EPS 1e-15  /* порог для проверки деления на ноль */

typedef enum CALC_ERR
{
	CALC_OK = 0,         /* выражение успешно вычислено */
	CALC_DIV_BY_ZERO,    /* деление на ноль */
	CALC_INVALID         /* неверное выражение */
} calc_err;

double sum(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div_op(double a, double b);

int precedence(char op);
int is_operator(char c);
calc_err apply_op(List<double> &values, char op);
calc_err apply_top(List<double> &values, List<char> &ops);
calc_err calculate(const char *expr, double *result);

int main(void)
{
	char line[1024];
	calc_err err = CALC_OK;
	double result = 0;

	while (1)
	{
		printf("Enter expression:\n");
		if (!fgets(line, sizeof(line), stdin))
		{
			break;
		}

		err = calculate(line, &result);
		if (err == CALC_INVALID)
		{
			printf("Invalid expression\n");
			continue;
		}
		if (err == CALC_DIV_BY_ZERO)
		{
			printf("Division by zero\n");
			continue;
		}

		printf("result = %lf\n", result);
	}

	return 0;
}

/* Чем больше число — тем выше приоритет операции */
int precedence(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

int is_operator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

/*
 * Выполнить одну операцию: снять два числа со стека values,
 * посчитать, положить результат обратно.
 * Возвращает CALC_OK, CALC_DIV_BY_ZERO или CALC_INVALID.
 */
calc_err apply_op(List<double> &values, char op)
{
	double b = 0;
	double a = 0;
	double res = 0;

	if (values.empty())
	{
		return CALC_INVALID;
	}

	b = values.top();
	values.pop();

	if (values.empty())
	{
		return CALC_INVALID;
	}

	a = values.top();
	values.pop();

	switch (op)
	{
	case '+':
		res = sum(a, b);
		break;
	case '-':
		res = sub(a, b);
		break;
	case '*':
		res = mul(a, b);
		break;
	case '/':
		if (fabs(b) < EPS)
		{
			return CALC_DIV_BY_ZERO;
		}
		res = div_op(a, b);
		break;
	default:
		return CALC_INVALID;
	}

	values.push(res);
	return CALC_OK;
}

/* Снять оператор с вершины ops и применить к values */
calc_err apply_top(List<double> &values, List<char> &ops)
{
	char op = ops.top();

	ops.pop();
	return apply_op(values, op);
}

/*
 * Алгоритм Дейкстры (два стека):
 *    values — числа, ops — операторы и скобки.
 * Читаем выражение слева направо и сразу считаем.
 */
calc_err calculate(const char *expr, double *result)
{
	List<double> values;
	List<char> ops;
	int last_was_value = 0;  /* 1, если только что прочитали число или ')' */
	const char *p = expr;
	calc_err err = CALC_OK;

	while (*p)
	{
		while (isspace((unsigned char)*p))
		{
			p++;
		}

		if (*p == '\0' || *p == '\n')
		{
			break;
		}

		/* Число (в т.ч. отрицательное: минус в начале или после оператора) */
		if (isdigit((unsigned char)*p) || *p == '.' ||
		    (*p == '-' && !last_was_value))
		{
			char *end = NULL;
			double val = strtod(p, &end);

			if (end == p)
			{
				err = CALC_INVALID;
				break;
			}

			values.push(val);
			p = end;
			last_was_value = 1;
			continue;
		}

		/* '(' — откладываем, начало подвыражения */
		if (*p == '(')
		{
			ops.push('(');
			p++;
			last_was_value = 0;
			continue;
		}

		/* ')' — считаем всё до '(' , затем убираем '(' */
		if (*p == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				err = apply_top(values, ops);
				if (err != CALC_OK)
				{
					break;
				}
			}

			if (err != CALC_OK)
			{
				break;
			}

			if (ops.empty() || ops.top() != '(')
			{
				err = CALC_INVALID;
				break;
			}

			ops.pop();
			p++;
			last_was_value = 1;
			continue;
		}

		/*
		 * Оператор: пока на вершине ops стоит операция
		 * с приоритетом не ниже текущей — выполняем её.
		 * Затем кладём текущий оператор в стек.
		 */
		if (is_operator(*p))
		{
			while (!ops.empty() && ops.top() != '(' &&
			       precedence(ops.top()) >= precedence(*p))
			{
				err = apply_top(values, ops);
				if (err != CALC_OK)
				{
					break;
				}
			}

			if (err != CALC_OK)
			{
				break;
			}

			ops.push(*p);
			p++;
			last_was_value = 0;
			continue;
		}

		err = CALC_INVALID;
		break;
	}

	/* Досчитываем оставшиеся операции */
	while (err == CALC_OK && !ops.empty())
	{
		if (ops.top() == '(')
		{
			err = CALC_INVALID;
			break;
		}

		err = apply_top(values, ops);
	}

	if (err == CALC_OK && values.empty())
	{
		err = CALC_INVALID;
	}

	if (err == CALC_OK)
	{
		*result = values.top();
	}

	// Освобождение памяти del_list/del_op_list происходят автоматически при выходе из функции через деструктор ~List()
	return err;
}

/* --- Базовые арифметические операции --- */

double sum(double a, double b)
{
	return a + b;
}

double sub(double a, double b)
{
	return a - b;
}

double mul(double a, double b)
{
	return a * b;
}

double div_op(double a, double b)
{
	return a / b;
}