
#include "stack.h"
#include <unistd.h>


//STACK!!!
struct stack_t_
{
        double*     data;
            int     counter;
            int     len;

};

//================CONSTANTS============================
const int MAX_STACK = 1000000;

//================DESCRIPTIONS OF ERRORS===============
const char* ERRDESCRIP[] =
{
    "START",
    "ERROR! Trying to work with null address!\n",
//==============================================
//STACK ERRORS
//==============================================
    "ERROR! Stack counter isn't in range(0, len of stack)!\n",
    "ERROR! Stack length isn't in range(0, MAX LEN)!\n",
    "ERROR! Trying pop empty stack!\n",
    "ERROR! Trying push full stack!\n",
    "ERROR! Can't open log file!\n",
//==============================================
//CPU ERRORS
//==============================================
    "NO ERROR!"

};


//================FUNCTIONS============================
int stack_Ctor(stack_t** _this, int length)
{

    stack_t* stk  = (stack_t*) calloc(sizeof(*stk), 1);

    ISNOTNULL(stk);

    if (0 < length && length < MAX_STACK) stk->len = length;
    else return ELENOUTLIM;

    stk->data = (double*) calloc(stk->len, sizeof(double));
    stk->counter = 0;

    if (!stk->data) return ENULLPTR;

    *_this = stk;

    return 0;
}

int stack_Push(stack_t* _this, double value)
{
    ISOKSTK(_this);

    if(_this->counter == _this->len) return EPUSH;

    _this->data[_this->counter] = value;
    (_this->counter)++;

    ISOKSTK(_this);

    return 0;
}

int stack_Pop(stack_t* _this, double* value)
{
    ISOKSTK(_this);
    ISNOTNULL(value);

    if(_this->counter == 0) return EPOP;

    (_this->counter)--;
    *value = _this->data[_this->counter];

    ISOKSTK(_this);

    return 0;
}

int stack_Ok(stack_t* _this)
{

    ISNOTNULL(_this);
    ISNOTNULL(_this->data);
    ISLENINLIM(_this)
    ISCNTINLIM(_this);

    return 0;
}

int stack_Print(stack_t* _this)
{
    ISOKSTK(_this);
    if (_this->counter == 0) printf("Stack is empty.\n");
    for(int i = _this->counter-1; i >= 0; i--)
        printf("#%d\t%lg\n", i+1, _this->data[i]);

    return 0;
}

int stack_Dump(stack_t* _this)
{
    ISNOTNULL(_this);

    int is_OK = stack_Ok(_this);
    fprintf(stderr, "-----------------------\n");
    fprintf(stderr, "STACK[0x%x] %s \n",
             _this, ((!is_OK)? "OK" : "!!!BAD!!!"));
    if(is_OK) fprintf(stderr, "ERROR NUMBER %d", is_OK);

    if(_this) fprintf(stderr, "\tCOUNT = %d\n"
                "\tDATA[0x%x], max %d\n\n",
                _this->counter, _this->data, _this->len);

    if(_this->data)
        for(int i = 0; i < _this->len; i++)
            fprintf(stderr, "\t\t[%d] = %lg %c\n", i, _this->data[i],
                ((i < _this->counter)? '*' : ' '));

    //fprintf(stderr, "\n\n");
    if(stderr != stdout) fflush(stderr);

    return 0;
}

int stack_Dtor(stack_t* _this)
{
    ISNOTNULL(_this);

    free(_this->data);
    _this->data = NULL;

    _this->counter = -1;

    _this = NULL;
    return 0;

}

int error_processing(stack_t* _this, int errnum)
{
    if (!errnum) return 0;

    stack_Dump(_this);
    end_logging();

    fprintf(stderr, "%s", ERRDESCRIP[errnum - STARTERRORS]);

}

int start_logging(char* log_file)
{
    ISNOTNULL(log_file);

    fflush(stderr);
    fclose(stderr);

    if(!freopen(log_file, "w", stderr)) return ELOGFILE;

    return 0;
}

int end_logging()
{
    fflush(stderr);
    fclose(stderr);

    dup2(fileno(stdout), fileno(stderr));

    return 0;
}
