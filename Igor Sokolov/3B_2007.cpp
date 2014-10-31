#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**
Соколов Игорь 453
Вариант 3
Задача B
*/

int Get_Prime_Number(int n)
{
    int Current_Number = 1;
    int i = 0;
    int IS_PRIME = 0;
    while(n>0)
    {
        IS_PRIME = 1;
        Current_Number++;

        for (i=2; i<Current_Number; i++)
            if (Current_Number%i==0)
				IS_PRIME = 0;

        if (IS_PRIME)
        {
            n--;
        }
    }
    return Current_Number;
}

int main()
{
    int* Numbers=(int*)calloc(10000,sizeof(int));		//Numbers
	int Prime;	//Prime
	assert(Numbers);
    int N;
	assert( scanf("%d", &N));
    for (int i=0;i<N;i++)
		assert(scanf("%d", &Numbers[i]));
     for (int i=0;i<N;i++)
	 {
		 Prime = Get_Prime_Number(Numbers[i]);
		 printf("%d ", Prime);
	 }

    return 0;
}
