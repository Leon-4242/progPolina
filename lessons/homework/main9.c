#include <stdio.h>
#include <math.h>

#define EPS 1e-15

int function(FILE*, double, double, double, double);

int main(void)
{
    
    FILE* in;
    FILE* out;
    double c1 = 0, c2 = 0, c3 = 0, b = 0;

    printf("Enter c1 c2 c3 b:\n");

    if (scanf("%lf %lf %lf %lf", &c1, &c2, &c3, &b) != 4) 
    {
        printf("Incorrect data\n");
        return -1;
    }

    in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Error input\n");
        return -2;
    }
    
    
    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Error output\n");
        return -3;
    }

    if (function(in, c1, c2, c3, b))
    {
        fprintf(out, "YES\n");
    } 
    else
        fprintf(out, "NO\n");

    fclose(in);
    fclose(out);

    return 0;
}

int function(FILE* in, double c1, double c2, double c3, double b)
{
    double a1 = 0, a2 = 0, a3 = 0;
    int flag = 1;

    if (fscanf(in, "%lf %lf %lf", &a1, &a2, &a3) == 3)
    {
        do
        {
            if (fabs(c1 * a1 + c2 * a2 + c3 * a3 - b) > EPS)
            {
                flag = 0;
            }
            a1 = a2;
            a2 = a3;
        } 
        while (flag && fscanf(in, "%lf", &a3) == 1);
    }

    return flag;
}
