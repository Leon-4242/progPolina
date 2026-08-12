#include <stdio.h>
#include <math.h>

#define EPS 1e-15

int function(FILE*, double, double*, double*);

int main(void)
{
    
    FILE* in;
    FILE* out;
    double x = 0, polinom = 0, diff = 0;

    printf("Enter x:\n");

    if (scanf("%lf", &x) != 1) 
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

    if (function(in, x, &polinom, &diff))
    {
        fprintf(out, "P(x) = %lf\nP'(x) = %lf\n", polinom, diff);
    } 
    else
        fprintf(out, "Empty file\n");

    fclose(in);
    fclose(out);

    return 0;
}

int function(FILE *in, double x, double* polinom, double* diff) {
    double a = 0, P = 0, diffP = 0;
    int n = 0;

    while (fscanf(in, "%lf", &a) == 1) 
    {
        
        P += a * pow(x, n);

        if (n > 0) 
        {
            diffP += n * a * pow(x, n - 1);
        }

        n++;
    }

    if (n == 0) 
    {
        return 0;
    }

	if (!feof(in))
	{
		return 0;
	}

    *polinom = P;
    *diff = diffP;
    return 1;
}
