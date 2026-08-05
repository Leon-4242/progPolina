#include <stdio.h>
#include <math.h>
#define EPS 1e-15

double function (FILE *file);
int main (void)
{
    FILE *in = fopen("input.txt", "r");
    if(in == NULL)
    {
        printf("Error input\n");
        return 1;
    }

    FILE *out = fopen("output.txt", "w");
    if(out == NULL)
    {
        printf("Error output\n");
        return 2;
    }
    fprintf(out, "%lf\n", function(in);
    fclose(in);
    fclose(out);

    return 0;
}

double function (FILE *in)
{
    double a = 0;
    double prod, power = 1;
    int count = 0;


    while (fscanf(in, "%lf", &a) == 1)
    {
        if(a <= EPS)
        {
            printf("not a positive number\n");
            return 3;
        }
        prod *= a;
        count++;
    }
    if(count == 0)
    {
        printf("Empty file\n");
        return 0;
    }
    power = 1.0/count;
    if (power <= EPS)
    {
        printf("sequence of numbers is too long\n");
        return 4;
    }
     return pow(prod, power);
}

