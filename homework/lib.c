#include <stdio.h>
int checker(FILE *in);
int interface(void) {
    char filename[20];
    FILE *in = NULL;
    int result = 0;

    printf("Enter filename: ");
    if (scanf("%s", filename) != 1) 
    {
        printf("Error: incorrect filename.\n");
        return -1;
    }

    in = fopen("input.txt", "r");
    if (!in) 
    {
        printf("Error: can't open file.\n");
        return -2;
    }

    result = checker(in);

    if (result == -3) {
        printf("Error: error occurred when reading data from a file.\n");
    } else {
        printf("Результат: %d\n", result);
    }

    fclose(in);
    return 0;
}


int checker(FILE *in) {
    int curr = 0, prev = 0, pprev = 0;
    int result = 1;


    if (fscanf(in, "%d", &curr) != 1) {
        return 1;
    }


    if (fscanf(in, "%d", &prev) != 1) {
        return 1; 
    }

    while (fscanf(in, "%d", &pprev) == 1) {
        if (prev + curr - pprev) {
            result = 0; 
            break;
        }
    
        curr = prev;
        prev = pprev;
    }

    if (ferror(in)) {
        return -3; 
    }

    return result; 
}
