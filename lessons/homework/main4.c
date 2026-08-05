#include <stdio.h>

int function(FILE *in);

int main(void)
{

    FILE *in = fopen("input.txt", "r");
    if (in == NULL)
    {
        printf("Error input\n");
        return 1;
    }
    

    FILE *out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Error output\n");
        return 2;
    }

    fprintf(out, "%d\n", function(in));
    fclose(in);
    fclose(out);

    return 0;
}

int function(FILE *in)
{
    double prev, curr = 0;
    int count = 0;

    if(fscanf(in, "%lf", &prev) != 1)
    {
        printf("Empty file\n");
        return -1;
    }

    while (fscanf(in, "%lf", &curr) == 1)
    {
        if(curr > prev)
        {
            count++;
        }
        prev = curr;
        
    }

    return count;
}
