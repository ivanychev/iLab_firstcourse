#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/*
Соколов Игорь 453
Вариант 3
Задача C
*/
int Solution(int n) // Не самое быстрое решение на мой взгляд, но другого не придумал 
{
   int a = 0, 
	   b = 0, 
	   c = 0, 
	   d = 0;
   int SQR = sqrt((double)n);
   for(a=1;a<=SQR;a++)
   for(b=0;b<=a;b++)
   for(c=0;c<=b;c++)
   for(d=0;d<=c;d++)
   if (a*a+b*b+c*c+d*d==n)
		{
			printf("%d %d %d %d\n",a*a,b*b,c*c,d*d);
			return 0;
		}
   return 1;
}



int main()
{
    unsigned int N=0;
    assert(scanf("%ud",&N)==1);
    assert(Solution(N)==0);

    return 0;
}
