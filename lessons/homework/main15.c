#include <stdio.h>

int function(FILE* in, double* res);

int main(void)
{
    double res = 0;

    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Error input\n");
        return -1;
    }
    

   if (!function(in, &res))
    {
        return -2; 
    }

    FILE *out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Error output\n");
        return -3;
    }

    fprintf(out, "%lf\n", res);
    fclose(in); 
    fclose(out);

    return 0;
}

int function(FILE* in, double* res)
{
    double a = 0, sum1 = 0, sum2 = 0;
    int count = 0;

    while (fscanf(in, "%lf", &a) == 1)
    {
        sum1 += a;
        sum2 += a*a;
        count++;
    }

    if (count == 0)
    {
        printf("Empty file\n");
        return 0; 
    }

    *res = sum2 / count - (sum1 / count)*(sum1 / count);
    return 1;
}
