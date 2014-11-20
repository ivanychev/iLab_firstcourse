#include "stack.cpp"
//Supported commands:
//0-exit
//1-push  argument:    1-register,0-value
//2-pop   argument:    1-register,0-value
//4-add
//3-ja
//5-mul
//6-jmp
//7-sqrt
//8-div
//:n-label n
//Supported registers:
//ax,bx,cx,dx
enum coms{
    EXIT,
    PUSH,
    POP,
    JA,
    ADD,
    MUL,
    JMP,
    SQRT,
    DIV,
    CRASH   = 10,
    CALL    = 11,
    RET     = 12
};
//const int EXIT=0,PUSH=1,POP=2,JA=3,ADD=4,MUL=5,JMP=6,SQRT=7,DIV=8,CRASH=10,CALL=11,RET=12;



struct commands
{
    int Count=0;
    int* type=NULL;
    int* argument=NULL;
    double* value=NULL;
};



struct cpu
{
    int currcommand;//total command amount
    commands coms;
    stackt st,functst;
    double ax,bx,cx,dx;//registers
};

cpu CPU_;

int readcommands(FILE *&F,cpu *CPU);

int CPUdocommands(cpu *CPU,FILE *&F2);

int cpuinitialize(cpu *CPU);
