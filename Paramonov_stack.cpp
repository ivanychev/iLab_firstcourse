#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

const double FAIL_POP=13.666;
struct stackt
{
    int Count=-99;
    double* value=new double;
};

int stack_push(stackt *st,double value)
{
    if (st->Count>-1)
    {
        st->value=(double*)realloc(st->value,sizeof(double)*(st->Count+1));

        st->value[st->Count++]=value;

        return 0;
    }
    else return 1;
}

double stack_pop(stackt *st)
{
    if (st->Count>0)
        return st->value[--st->Count];
    else
    {
        printf("STRUCT IS EMPTY OR ISNT CREATED,CAN'T POP!\n");

        return FAIL_POP;

    }
}

double mul(stackt *st)//a*b
{

    double a=st->value[--st->Count];
    double b=st->value[--st->Count];
    st->value[st->Count++]=a*b;
    return 0;
}

void stack_ctor(stackt *st)
{
    st->Count=0;
//st->value=new double;
}

void stack_dtor(stackt *st)
{
    st->Count=-2;

}

void stack_print(stackt *st)
{
    for(int i=st->Count-1;i>=0;i--)printf("COUNT=%d VALUE=%lg\n",i,st->value[i]);
if (st->Count<0)printf("STRUCT IS EMPTY OR ISNT CREATED!\n");
}

int main()
{
    stackt st;

    double forpush;
    double forpop=999;
    char* command=new char;
    char c;
    do
    {
        command[0]='\0';
        command[1]='\0';
        command[2]='\0';
        command[3]='\0';
        for (int i=0; i<4; i++)
        {
            scanf("%c",&c);
            if((c!='\n')&&(c!=' '))
            {
                command[i]=c;
            }
            else break;

        }
        if(command[0]=='p'&&command[1]=='u'&&command[2]=='s'&&command[3]=='h')
        {
            scanf("%lg",&forpush);
            stack_push(&st,forpush);
        }

        if(command[0]=='p'&&command[1]=='o'&&command[2]=='p')
        {
            forpop=stack_pop(&st);
            if (forpop!=FAIL_POP)printf("%lg\n",forpop);
        }

if(command[0]=='c'&&command[1]=='r'&&command[2]=='e'&&command[3]=='a')stack_ctor(&st);
if(command[0]=='d'&&command[1]=='e'&&command[2]=='s'&&command[3]=='t')stack_dtor(&st);
if(command[0]=='l'&&command[1]=='o'&&command[2]=='g')stack_print(&st);

    }
    while(command[0]!='e'||command[1]!='x'||command[2]!='i'||command[3]!='t');


    return 0;
}
