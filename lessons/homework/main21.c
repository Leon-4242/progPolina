#include <stdio.h>

int function(FILE* in, int* res);

int main(void)
{
    int res = 0;

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

    fprintf(out, "%d\n", res);
    fclose(in); 
    fclose(out);

    return 0;
}

int function(FILE *in, int *res) 
{
    
    int prev = 0, curr = 0, sum = 0, maxsum = 0, len = 1, reslen = 1;


    if (fscanf(in, "%d", &prev) != 1) 
    {
        return 0;
    }
        

    while (fscanf(in, "%d", &curr) == 1) 
    {
        if (curr == prev) 
        {
            len++;
            sum += curr;
        } else 
        {
             prev = curr;
            len = 1;
            sum = curr;
        }

        if (sum > maxsum) 
            {
                maxsum = sum;
                reslen = len;
            }
    }

    *res = reslen;
    return 1;
}
