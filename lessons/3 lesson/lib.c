#include "lib.h"

int interface(void) {
	char filename[20];
	FILE *in = NULL;
	int result = 0;

	if (scanf("%s", filename) != 1) {
		printf("ERROR: incorrect filename.\n");
		return -1;
	}

	in = fopen(filename /*="input.txt"*/, "r");
	if (!in /*in == NULL*/) {
		printf("ERROR: can't open file.\n");
		return -2;
	}
	// int k = 3;
	// if (k) {
	//		print("%d", k);
	// }
	// int *ptr = &k;
	// if (ptr) {
	//		print("%d", *ptr);
	// }
	//
	// if ((ptr && k) || !(k-1) )
	
	result = checker(in);

	printf("result = %d", result);	
	fclose(in);

	return 0;
}

int checker(FILE *in) {
	int n = 0;
	int curr = 0, prev = 0, pprev = 0;
	int result = 1;
	
	if (fscanf(in, "%d", &pprev) != 1) {
		return 1;
	}
	
	if (fscanf(in, "%d", &prev) != 1) {
		return 1;
	}

	while (fscanf(in, "%d", &curr) == 1) {
		if (prev+curr-pprev) {
			result = 0;
			break;
			//continue;
			//printf("1");
		}
		pprev = prev;
		prev = curr;
	}

	//if (!n) {
	//	return -1;
	//}

	if (feof(in)) {
		return -2;
	}

	if (ferror(in)) {
		return -3;
	}

	//rewind(in);
	//
	//for (i = 0; i < n; ++i) {
	//	fscanf(in, "%lf", &curr);
	//	printf("%d", curr);
	//}
	// int k;
	// 
	// k  = 0;
	// printf("%d\n", ++k);
	// 
	// k = 0;
	// printf("%d\n", k++);
	//
	//
	// n = k;
	// ++k;
	// одно и то же
	// n = k++;

	return result;
}
