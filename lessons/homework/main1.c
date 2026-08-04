#include <stdio.h>

double function(FILE *in);

int main(void)
{
    double result;

    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Error input\n");
        return 1;
    }

    result = function(in);
    fclose(in);

    FILE *out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Error output\n");
        return 2;
    }

    fprintf(out, "%lf\n", result);
    fclose(out);

    return 0;
}

double function(FILE *in)
{
    double a, sum = 0;
    int count = 0;

    while (fscanf(in, "%lf", &a) == 1)
    {
        sum += a;
        count++;
    }

    if (count == 0)
    {
        printf("Empty file\n");
        return 0; 
    }

    return sum / count;
}