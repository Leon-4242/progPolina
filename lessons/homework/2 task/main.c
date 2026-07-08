#include <stdio.h>
#include "HomeWork 1Lib.h"

int main(void)
{
    FILE *in = NULL;
	double a, b, c, x, result;
/*
	char *filename = NULL;
	filename = (char*)malloc(n*sizeof(char));
*/ /*
	char filename[20];
*/
	in = fopen("data.txt", "r");
	fscanf(in, "%lf", &a);

	out = fopen("result.txt", "w");
	fprintf(out, "%lf", res);

	fclose(in);
	fclose(out);

    printf("Enter coefficients: ");
    scanf( "%lf %lf %lf", &a, &b, &c);
    printf("Enter x: ");
    scanf("%lf", &x);
	/*
    result = function(a, b, c, x);
    printf("Result: %lf ", result);
    */
	printf("a = %lf\n", a);
    printf("Result: %lf \n", function(a, b, c, x));

	printf("a = %lf\n", a);
	return 0;
}
