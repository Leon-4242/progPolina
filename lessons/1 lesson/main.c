#include <stdio.h>

int main(void) {
	int a = 0;

	printf("текущее значение a = %d\n", a);
	printf("Введите число: ");
	scanf("%d", &a);

	a *= a;

	printf("текущее значение a = %d\n", a);
	return 0;
}
