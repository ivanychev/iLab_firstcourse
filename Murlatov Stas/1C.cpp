#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
Вариант 1
Задача C
*/
int Check(unsigned int N)
{
    if (N<4)
    {
        if(N==1)return 1;
        else return 0;
    }

    if ((N-2)%4==0)return 0;
    else
    {
        return Check(int(N/4.0+0.5));
    }

}

int main()
{
    unsigned int n;
    assert (scanf("%ud",&n)==1);
	printf(Check(n)? "YES" : "NO");
    return 0;
}