#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**
Соколов Игорь 453
Вариант 2
Задача C
*/

int Get_Prime_Number(unsigned int n)
{
    int Current_Number=1;
    int i=0;
    int IS_PRIME=0;
    while(n>0)
    {
        IS_PRIME=1;
        Current_Number++;

        for (i=2; i<Current_Number; i++)
            if (Current_Number%i==0) IS_PRIME=0;

        if (IS_PRIME)
        {
            n--;
        }
    }
    return Current_Number;
}



int main()
{
	unsigned int N = 0;
	printf("Enter N> ");
    assert(scanf("%ud",&N)==1);
    int Result=Get_Prime_Number(N);
    printf("%ud",Result);
    return 0;
}
