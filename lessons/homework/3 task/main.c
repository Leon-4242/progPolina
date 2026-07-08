#include "average square value.h"

int main(void)
{
    double x, y;
    FILE* filename;

    printf("Enter 2 numbers: ");
    scanf("%lf %lf", &x, &y);

    function(x, y);

    filename = fopen("out.txt", "w");
    fprintf(filename, "%lf", function(x, y));


    return 0;
}

