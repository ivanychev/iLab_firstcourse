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


int stack_ok(stackt *st);

int stack_push(stackt *st,double value);

double stack_pop(stackt *st);

int add(stackt *st);

int sqrt(stackt *st);

int mul(stackt *st);

int div(stackt *st);//a*b


int stack_ctor(stackt *st);

int stack_dtor(stackt *st);

int stack_print(stackt *st);
