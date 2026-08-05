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


