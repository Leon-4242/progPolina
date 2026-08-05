#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"

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
calc_err apply_op(list *values, char op);
calc_err apply_top(list *values, op_list *ops);
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
calc_err apply_op(list *values, char op)
{
	double b = 0;
	double a = 0;
	double res = 0;

	if (empty(values))
	{
		return CALC_INVALID;
	}

	b = value(values);
	pop_back(values);

	if (empty(values))
	{
		return CALC_INVALID;
	}

	a = value(values);
	pop_back(values);

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

	push_back(values, res);
	return CALC_OK;
}

/* Снять оператор с вершины ops и применить к values */
calc_err apply_top(list *values, op_list *ops)
{
	char op = top_op(ops);

	pop_op(ops);
	return apply_op(values, op);
}

/*
 * Алгоритм Дейкстры (два стека):
 *   values — числа, ops — операторы и скобки.
 * Читаем выражение слева направо и сразу считаем.
 */
calc_err calculate(const char *expr, double *result)
{
	list *values = make_list();
	op_list *ops = make_op_list();
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

			push_back(values, val);
			p = end;
			last_was_value = 1;
			continue;
		}

		/* '(' — откладываем, начало подвыражения */
		if (*p == '(')
		{
			push_op(ops, '(');
			p++;
			last_was_value = 0;
			continue;
		}

		/* ')' — считаем всё до '(' , затем убираем '(' */
		if (*p == ')')
		{
			while (!empty_op(ops) && top_op(ops) != '(')
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

			if (empty_op(ops) || top_op(ops) != '(')
			{
				err = CALC_INVALID;
				break;
			}

			pop_op(ops);
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
			while (!empty_op(ops) && top_op(ops) != '(' &&
			       precedence(top_op(ops)) >= precedence(*p))
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

			push_op(ops, *p);
			p++;
			last_was_value = 0;
			continue;
		}

		err = CALC_INVALID;
		break;
	}

	/* Досчитываем оставшиеся операции */
	while (err == CALC_OK && !empty_op(ops))
	{
		if (top_op(ops) == '(')
		{
			err = CALC_INVALID;
			break;
		}

		err = apply_top(values, ops);
	}

	if (err == CALC_OK && empty(values))
	{
		err = CALC_INVALID;
	}

	if (err == CALC_OK)
	{
		*result = value(values);
	}

	del_list(values);
	del_op_list(ops);
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
