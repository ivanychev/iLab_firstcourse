#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/*
Вариант 10
Задача C
*/
int Solution(int n)
{
	int a = 0,
		b = 0,
		c = 0;
	int SQR = sqrt((double)n);
	for (a = 1; a <= SQR; a++)
	for (b = 0; b <= a; b++)
	for (c = 0; c <= b; c++)
	if (a*a + b*b + c*c == n)
	{
		printf("%d %d %d\n", a*a, b*b, c*c);
		return 0;
	}
	return -1;
}


int main()
{
	unsigned int N = 0;
	assert(scanf("%ud", &N) == 1);
	if (Solution(N) == -1)
		printf("-1\n");
	return 0;
}
