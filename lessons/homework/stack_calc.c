#include "stack.h"
#include "stdio.h"

int main(void)
{
	list * stack = make_list();
	double a, b, buff1, buff2;
	char c;

	while (1)
	{
		//TODO: добавить проверки, выход из цикла и т.д.
		scanf(" %lf %lf %c", &a, &b, &c);

		push_back(stack, a);
		push_back(stack, b);

		func = function(c);

		buff = value(stack);
		pop_back(stack);

		buff = func(value(stack), buff);
		pop_back(stack);

		push_back(buff);
	}

	del_list(stack);
	return 0;	
}

//6/3
// 6 3 /
//7 8 1 * +
//7+8*1


#include "stack.h"

int main (void)
{
    list * stack = make_list();
    operation number = SUM;
    double a, b, buff = 0;
    func f;

    while (1)
    {
        if (data_check (&number, &a, &b) != 0)
        {
            continue;
        }

        push_back(stack, a);
        push_back(stack, b);

        f = function(number);

        buff = value(stack);
        pop_back(stack);

        buff = f(value(stack), buff);
        pop_back(stack);

        push_back(stack, buff);

    }

    del_list(stack);
    return 0;
}


