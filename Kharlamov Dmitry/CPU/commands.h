#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

const int CODE_SIZE = 256;


enum COMMANDS
{
    BEGIN,
    PUSH,
    POP,
    OK,
    DUMP,
    ADD,
    SUB,
    MUL,
    DIR,
    SIN,
    COS,
    SQRT,
    JA,
    JAE,
    JB,
    JBE,
    JE,
    JNE,
    JMP,
    OUT,
    END

};

enum REGIST
{
    NUM = 100,
    REG = 110,
    AX  = 111,
    BX  = 112,
    CX  = 113,
    DX  = 114

};

const char* S_CMD[] =
{
    "begin",
    "push",
    "pop",
    "ok",
    "dump",
    "add",
    "sub",
    "mul",
    "dir",
    "sin",
    "cos",
    "sqrt",
    "ja",
    "jae",
    "jb",
    "jbe",
    "je",
    "jne",
    "jmp",
    "out",
    "end"

};

const char* S_REG[] =
{
    "ax",
    "bx",
    "cx",
    "dx"

};


#endif // COMMANDS_H_INCLUDED
