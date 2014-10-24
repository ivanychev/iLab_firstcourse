#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
/**
Соколов Игорь, 453
Вариант 6
Задача C
*/
int Check(int n)
{
	int i;
    for (i=2; i<=sqrt((double)n); i++)
	if ((n%(i*i))==0)
		return 0;
    return 1;
}


int main()
{
    int N=0;
    assert(scanf("%d",&N));

    int* Numbers=new int;
	assert(Numbers);

	int Check_Result;

    for(int i=0; i<N; i++)
    {
        assert(scanf("%d",&Numbers[i]));
    }

    for(int i=0; i<N; i++)
    {
		Check_Result = Check(Numbers[i]);
		if (Check_Result)  
			printf("%d ", Numbers[i]);
    }
	printf("\n");
    return 0;
}
