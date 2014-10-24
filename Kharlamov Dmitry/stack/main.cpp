/**
    @file
    My realization of data structure STACK of real numbers
    with processing errors

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.1
*/

#include "stack.h"
#include "io.h"

int main(int argc, char *argv[])
{

    if (argc >= 2 && strcmp(argv[1], "-logs"))
    {
      if (argc == 3 && !(start_logging(argv[2])));
        else start_logging("logs.txt");
    }



    stack_interface(stdout);

    /*
    printf("Write len of stack(1..1000000)");
    int len = 0;
    scanf("%d", &len);

    OK(stack_Ctor(&stk, len), stk);

    OK(stack_Push(stk, 10), stk);
    OK(stack_Push(stk, 20), stk);
    OK(stack_Push(stk, 30), stk);
    //stk->data[2] = 77;
    stack_Dump(stk);
    stack_Print(stk);
    double i = 0;

    OK(stack_Pop(stk, &i), stk);

    OK(stack_Pop(stk, &i), stk);

    OK(stack_Pop(stk, &i), stk);
    stack_Print(stk);

    //OK(stack_Pop(stk, &i));

    stack_Dtor(stk);

    end_logging();
    */
    return 0;
}

