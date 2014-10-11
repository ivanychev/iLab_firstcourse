/**
    @file
    My realization of data structure STACK of real numbers
    with processing errors

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.0
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#define ISOKSTACK( cond ) if (!stack_Ok(cond)) { stack_Dump(cond); return 0; }

#define ISNOTNULL( cond ) if (!(cond)) { last_stack_error = ENULLPTR; return 0; }
#define ISINLIMIT( cond ) if (!(0 <= (cond->counter) && (cond->counter) < MAX_LEN_STACK)) \
{ last_stack_error = EOUTLIMIT; stack_Dump(cond); return 0; }

#define er( cond ) if(!(cond)) { printf(error_processing()); assert(0);}


//=============ERRORs CONST=============================

const int  ENULLPTR = 1000;
const int EOUTLIMIT = 1001;
const int     EPUSH = 1002;
const int      EPOP = 1003;

//==============CONSTANTS===============================

const int MAX_LEN_STACK = 20;
int last_stack_error = 0;
char* NAME_DUMP_FILE = "logs.txt";

//STACK!!!
struct stack_t
{
    double* data;
        int counter;

};

//=======INIT FUNTIONS FOR MANIPULATE STACK=============

int stack_Ctor( stack_t* _this);

int stack_Push(struct stack_t* _this, double value);

int stack_Pop(struct stack_t* _this, double* value);

int stack_Ok(struct stack_t* _this);

int stack_Dump(struct stack_t* _this);

int stack_Dtor(struct stack_t* _this);

char* error_processing();


int main()
{

    stack_t stk = {};
    double* a = (double*) calloc(MAX_LEN_STACK, sizeof(double));


    stack_Ctor(&stk);

    stack_Push(&stk, 10);
    stack_Push(&stk, 20);
    stack_Push(&stk, 30);

    stack_Dump(&stk);

    double i = 0;

    er(!stack_Pop(&stk, &i));
    printf("%lg\n", i);

    er(stack_Pop(&stk, &i));
    printf("%lg\n", i);

    er(stack_Pop(&stk, &i));
    printf("%lg\n", i);

    er(stack_Pop(&stk, &i));

    stack_Dtor(&stk);
    return 0;
}



int stack_Ctor(struct stack_t* _this)
{
    ISNOTNULL(_this);

    _this->data = (double*) calloc(MAX_LEN_STACK, sizeof(double));
    _this->counter = 0;

    ISNOTNULL(_this->data);

    return 1;
}

int stack_Push(struct stack_t* _this, double value)
{
    ISOKSTACK(_this);

    if(_this->counter == MAX_LEN_STACK) {last_stack_error = EPUSH; stack_Dump(_this); return 0;}

    _this->data[_this->counter] = value;
    (_this->counter)++;

    ISINLIMIT(_this);

    ISOKSTACK(_this);

    return 1;
}

int stack_Pop(struct stack_t* _this, double* value)
{
    *value = -13.666;

    ISOKSTACK(_this);

    if(_this->counter == 0) {last_stack_error = EPOP; stack_Dump(_this); return 0;}

    (_this->counter)--;
    *value = _this->data[_this->counter];

    ISOKSTACK(_this);

    return 1;
}

int stack_Ok(struct stack_t* _this)
{

    ISNOTNULL(_this);
    ISNOTNULL(_this->data);
    ISINLIMIT(_this);

    return 1;
}

int stack_Dump(struct stack_t* _this)
{
    FILE* logs = fopen(NAME_DUMP_FILE, "a");
    fprintf(logs, "STACK[0x%x] %s \n"
            "\tCOUNT = %d\n"
            "\tDATA[0x%x], max %d\n\n",
             _this, ((stack_Ok(_this))? "OK" : "!!!BAD!!!"),
             _this->counter, _this->data, MAX_LEN_STACK);

    for(int i = 0; i < MAX_LEN_STACK; i++)
        fprintf(logs, "\t\t[%d] = %lg %c\n", i, _this->data[i],
                ((i < _this->counter)? '*' : ' '));

    fclose(logs);
    return 1;
}

int stack_Dtor(struct stack_t* _this)
{
    free(_this->data);
    _this->data = NULL;

    _this->counter = -1;

    _this = NULL;
    return 1;

}

char* error_processing()
{
    switch(last_stack_error)
    {
    case ENULLPTR:
        return "ERROR! Trying to work with null address!\n";
    case EOUTLIMIT:
        return "ERROR! Stack counter isn't in range(0, MAX_LEN_STACK)!\n";
    case EPOP:
        return "ERROR! Trying push full stack!\n";
    case EPUSH:
        return "ERROR! Trying pop empty stack!\n";
    default:
        return "ERROR! Unknown error!\n";
    }

}
