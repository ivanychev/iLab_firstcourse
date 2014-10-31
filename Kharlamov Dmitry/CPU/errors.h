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
//==============================================
//CPU ERRORS
//==============================================
    NOERROR         = 1007

};





#endif // ERRORS_H_INCLUDED
