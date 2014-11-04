#include <stdio.h>
#include "errors.h"


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


int errlog(int errnum, char* file, int line)
{

    fprintf(stderr,
            "%s\nIn file: %s\nAt line: %d\n",
            err_to_str(errnum), file, line);

    return 0;
}

int errlog_var(int errnum, char* file,
               int line, char* variable)
{


    errlog(errnum, file, line);

    fprintf(stderr,
            "With variable: %s\n",
            variable);

    return 0;
}

char* err_to_str(int errnum)
{
    return (char*)ERRDESCRIP[errnum - STARTERRORS];
}
