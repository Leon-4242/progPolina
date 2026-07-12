#include <stdio.h>

int main (void)
{
    while (1)
    {
        int number = 0;
        double a = 0, b = 0, result = 0;
        printf("Enter the operation number: addition - 1, subtraction - 2, multiplication - 3, division - 4\n");
        scanf("%d", &number);
        if(number < 1 || number > 4)
        {
             printf("Incorrect operation number\n");
             continue;
        }
        printf("Enter two numbers:\n");
        scanf("%lf %lf", &a, &b);
        if (number == 1)
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
    }
    
    return 0;
}