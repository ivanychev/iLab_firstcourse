#include "processor.h"

/*
TODO:
    -   �������
    -   ������� ��� ��������
    -   ������ �� ����������� ���������� ����������
    -   ������ ���������� �����
    -   -> � * - ������� ����������
    --  ���� ������
    -   out ax, out ch 54, out 5 -  ����� � �������

*/

int readcommands(FILE *&F,cpu *CPU)
{
    if(!CPU)return NULL_ARGUMENT;

    int command = -2;
    double argument = -2, forpush = 0, forpop = 0;
    char c = ' ',b = ' ';
    do
    {

        CPU->coms.value=(double*) realloc((&(CPU)->coms)->value,sizeof(double)*( (CPU)->currcommand +1));
        assert((&(CPU)->coms)->value);
        (&(CPU)->coms)->argument=(int*) realloc((&(CPU)->coms)->argument,sizeof(int)*( (CPU)->currcommand +1));
        assert((&(CPU)->coms)->argument);
        (&(CPU)->coms)->type=(int*) realloc((&(CPU)->coms)->type,sizeof(int)*((CPU)->currcommand+1));
        assert((&(CPU)->coms)->type);
        if (!F)
        {
            FILE *F2=fopen("3.txt","w");
            fprintf(F2,"CODE NOT FOUND");
            break;
        }
        if(!feof(F))fscanf(F,"%d",&command);
        else command=0;


        switch (command)
        {
        case DIV:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=8;
            break;
        }
        case SQRT:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=7;
            break;
        }
        case JMP:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=6;
            fscanf(F,"%lg",&argument);
            (&(CPU)->coms)->argument[(CPU)->currcommand]=(int)argument;
            break;
        }
        case MUL:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=5;
            break;
        }
        case ADD:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=4;
            break;
        }
        case CALL:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=11;
            fscanf(F,"%lg",&argument);
            (&(CPU)->coms)->argument[(CPU)->currcommand]=(int)argument;
            break;
        }
        case RET:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=12;
            break;
        }
        case JA:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=3;
            fscanf(F,"%lg",&argument);
            (&(CPU)->coms)->argument[(CPU)->currcommand]=(int)argument;

        }
        break;
        case POP:
        {

            c=getc(F);
            if ((c=='\n')||(c==EOF))
            {
                (&(CPU)->coms)->type[(CPU)->currcommand]=2;
                (&(CPU)->coms)->argument[(CPU)->currcommand]=0;
            }
            else
            {
                (&(CPU)->coms)->type[(CPU)->currcommand]=2;
                (&(CPU)->coms)->argument[(CPU)->currcommand]=1;
                fscanf(F," %c",&b);
                *(char*)&(&(CPU)->coms)->value[(CPU)->currcommand]=b;
            }
            break;
        }


        case EXIT:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=EXIT;
            break;
        }

        case CRASH:
        {
            (&(CPU)->coms)->type[(CPU)->currcommand]=10;
            break;
        }
        case PUSH:
        {
            fscanf(F,"%lg",&argument);
            (&(CPU)->coms)->type[(CPU)->currcommand]=1;
            (&(CPU)->coms)->argument[(CPU)->currcommand]=(int)argument;
            if (argument==0)
            {

                fscanf(F,"%lg",&forpush);
                (&(CPU)->coms)->value[(CPU)->currcommand]=forpush;
            }
            if (argument==1)
            {
                fscanf(F," %c",&b);
                *(char*)&(&(CPU)->coms)->value[(CPU)->currcommand]=b;
            }

            break;
        }
        }

        (CPU)->currcommand++;
    }
    while(command!=EXIT);
}




int CPUdocommands(cpu *CPU,FILE *&F2)
{
    if(!CPU)return NULL_ARGUMENT;
    char c=' ';
    double forpush=0,forpop=0;   //c,forpush,forpop needed for input and output
    for (int i=0; i<(CPU)->currcommand-1; i++)
    {


        switch ((&(CPU)->coms)->type[i])
        {
        case CRASH:
            printf("CRASH AT %d LINE",i+1);
            abort();
            break;
        case ADD:
        {
            //forpush=stack_pop(&((CPU)->st));
            //forpop=stack_pop(&((CPU)->st));
            //assert(forpop==FAIL);
            //stack_push(&((CPU)->st),forpop+forpush);
            add(&((CPU)->st));
            break;
        }

        case MUL:
        {
            mul(&((CPU)->st));
            break;
        }
        case DIV:
        {

            if(div(&((CPU)->st))==1)
            {
                printf("DIVIZION BY ZERO IS FORBIDDEN!");
                abort();
            }
            break;
        }
        case SQRT:
        {
            sqrt(&((CPU)->st));
            break;
        }

        case JMP:
        {

            i=(&(CPU)->coms)->argument[i]-1;
            break;
        }

        case CALL:
        {
            stack_push(&((CPU)->functst),i);
            i=(&(CPU)->coms)->argument[i]-1;
            break;

        }
        case RET:
        {
            i=stack_pop(&((CPU)->functst));
            break;
        }
        case POP:
        {
            if ((&(CPU)->coms)->argument[i]==0)if((forpop=stack_pop(&((CPU)->st)))!=FAIL)fprintf(F2,"%lg\n",forpop);
            if ((&(CPU)->coms)->argument[i]==1)
            {
                c=*(char*)&(&(CPU)->coms)->value[i];
                if (c=='a')CPU->ax=stack_pop(&((CPU)->st));
                if (c=='b')CPU->bx=stack_pop(&((CPU)->st));
                if (c=='c')CPU->cx=stack_pop(&((CPU)->st));
                if (c=='d')CPU->dx=stack_pop(&((CPU)->st));
            }
            break;
        }

        case JA:
        {


            forpush=stack_pop(&((CPU)->st));
            forpop=stack_pop(&((CPU)->st));

            if(forpush>forpop)
            {
                i=(&(CPU)->coms)->argument[i]-1;
            }
            break;
        }

        case PUSH:
        {

            if ((&(CPU)->coms)->argument[i]==0)stack_push(&((CPU)->st),(&(CPU)->coms)->value[i]);
            if ((&(CPU)->coms)->argument[i]==1)
            {
                c=*(char*)&(&(CPU)->coms)->value[i];
                if (c=='a')stack_push(&((CPU)->st),CPU->ax);
                if (c=='b')stack_push(&((CPU)->st),CPU->bx);
                if (c=='c')stack_push(&((CPU)->st),CPU->cx);
                if (c=='d')stack_push(&((CPU)->st),CPU->dx);
            }
            break;
        }

        }
        if(i>=(CPU)->currcommand-1)
        {
            printf("JUMP TO INVALID VALUE %d!",(CPU)->currcommand-1);
            abort();
        }
    }

}

int CPU_ok(cpu *CPU)
{
    if (!CPU)return NULL_ARGUMENT;
    if (!(&CPU->st))return 1;
    if (!(&CPU->functst))return 1;
    return 0;
}

int CPU_dump(cpu *CPU)
{
    if(!CPU)return NULL_ARGUMENT;
    printf("ax=%lg bx=%lg cx=%lg dx=%lg",CPU->ax=0, CPU->bx=0, CPU->cx=0, CPU->dx=0);
    return 0;
}

int cpuinitialize(cpu *CPU)
{
    if(!CPU)return NULL_ARGUMENT;
    CPU->ax=0;
    CPU->bx=0;
    CPU->cx=0;
    CPU->dx=0;
    CPU->currcommand=0;
    stack_ctor(&(CPU->st));
    stack_ctor(&(CPU->functst));
}

int main()
{
    FILE *F2=fopen("3.txt","w");
    if(!F2)
    {
        printf("SOMETHINK WENT WRONG,CANNOT CREATE OUTPUT FILE");
        return 1;
    }
    FILE *F=fopen("2.txt","r");
    if (!F)
    {
        printf("SOMETHINK WENT WRONG,CANNOT OPEN INPUT FILE");
        return 1;
    }

    cpuinitialize(&CPU_);

    readcommands(F,&CPU_);

    CPUdocommands(&CPU_,F2);
    printf("%d",errno);
    return 0;

}



