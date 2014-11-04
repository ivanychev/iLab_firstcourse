#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

enum ERRORS
{
    STARTERRORS     = 1000,
    ENULLPTR        = 1001,
//==============================================
//STACK ERRORS
//==============================================
    ECNTOUTLIM      = 1002,
    ELENOUTLIM      = 1003,
    EPOP            = 1004,
    EPUSH           = 1005,
    ELOGFILE        = 1006,
    ERESIZE         = 1007,
//==============================================
//CPU ERRORS
//==============================================
    ECPUPUSH,
    EJMPBADLABEL,
    NOERROR

};





#define ISNOTNULL( ptr ) if (!ptr) {char* name = #ptr; /*errlog_var(ENULLPTR, __LINE__, __FILE__, name);*/ return ENULLPTR;}

// STACK VERIFIER MACROS
#define ISCNTINLIM( stack ) if (!(0 <= stack->counter && stack->counter < stack->len)) return ECNTOUTLIM;
#define ISLENINLIM( stack ) if (!(0 <= stack->len && stack->len < MAX_STACK)) return ELENOUTLIM;

// CPU VERIFIER MACROS

char* err_to_str(int errnum);

int errlog(int errnum, char* file, int line);

int errlog_var(int errnum, char* file, int line, char* variable);


#endif // ERRORS_H_INCLUDED
