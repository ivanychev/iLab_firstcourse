#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double FAIL=13.666;
const double FAIL_POP=13.666;
const int    POISON = -99;
const int    NULL_ARGUMENT=-1;

/*
TODO

    -    Проверка корректности возвращаемого значения стандартных функций
    -    NO C++ HERE


*/
struct stackt
{
    int Count = POISON;
    double* value = NULL;
};


int stack_ok(stackt *st)
{
    if(!st)return NULL_ARGUMENT;
    if ((st->Count >= 0) && (st->value != NULL)) return 0;
    return 1;
}

int stack_push(stackt *st,double value)
{
    if (!st)return NULL_ARGUMENT;
    if (stack_ok(st)==0)
    {

        st->value=(double*)realloc(st->value,sizeof(double)*(st->Count+1));
        assert(st->value);

        st->value[st->Count++]=value;

        return 0;
    }
    else return 1;

}

double stack_pop(stackt *st)
{
    if(!st)return FAIL_POP;
    if (stack_ok(st)==0)
        if (st->Count>0)
            return st->value[--st->Count];
        else
        {
            return FAIL_POP;
        }

}

int add(stackt *st)//a+b
{
    if(!st)return NULL_ARGUMENT;
    double a=st->value[--st->Count];
    double b=st->value[--st->Count];
    st->value[st->Count++]=a+b;
    if(st->value[st->Count-1]==-0.0)st->value[st->Count-1]=0.0;
    return 0;
}

int sqrt(stackt *st)//a+b
{
    if(!st)return NULL_ARGUMENT;
    double a=st->value[--st->Count];

    st->value[st->Count++]=sqrt(a);
    if(st->value[st->Count-1]==-0.0)st->value[st->Count-1]=0.0;
    return 0;
}

int mul(stackt *st)//a*b
{
    if(!st)return NULL_ARGUMENT;
    double a=st->value[--st->Count];
    double b=st->value[--st->Count];
    st->value[st->Count++]=a*b;
    if(st->value[st->Count-1]==-0.0)st->value[st->Count-1]=0.0;
    return 0;
}

int div(stackt *st)//a*b
{
    if(!st)return NULL_ARGUMENT;
    double a=st->value[--st->Count];
    double b=st->value[--st->Count];
    if (a!=0)
    {
        st->value[st->Count++]=b/a;
        if(st->value[st->Count]==-0.0)st->value[st->Count]=0.0;
        return 0;
    }

    return 1;
}

int stack_ctor(stackt *st)
{
    if(!st)return NULL_ARGUMENT;
    st->Count=0;
    st->value=(double*) calloc (1,sizeof(double));
    assert(st->value);
    return 0;
}

int stack_dtor(stackt *st)
{
    if(!st)return NULL_ARGUMENT;
    st->Count=-2;
    free(st->value);
    return 0;
}

int stack_print(stackt *st)
{
    if(!st)return NULL_ARGUMENT;
    for(int i=st->Count-1; i>=0; i--)printf("COUNT=%d VALUE=%lg\n",i,st->value[i]);
    if (st->Count<0)printf("STACK ISNT CREATED!\n");
    if (st->Count==0)printf("STACK IS EMPTY!\n");
}

