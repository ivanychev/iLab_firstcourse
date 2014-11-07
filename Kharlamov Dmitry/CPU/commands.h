#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

const int CODE_SIZE = 1024;


enum COMMANDS
{
    BEGIN   =  0,
    PUSH    =  1,
    POP     =  2,
    OK      =  3,
    DUMP    =  4,
    ADD     =  5,
    SUB     =  6,
    MUL     =  7,
    DIR     =  8,
    SIN     =  9,
    COS     = 10,
    SQRT    = 11,
    JA      = 12,
    JAE     = 13,
    JB      = 14,
    JBE     = 15,
    JE      = 16,
    JNE     = 17,
    JMP     = 18,
    OUT     = 19,
    MOV     = 20,
    INC     = 21,
    DEC     = 22,
    CALL    = 23,
    RET     = 24,
    END

};

enum REGIST
{
    NUM     = 100,
    NOARG   = 105,
    REG     = 110,
    AX      = 111,
    BX      = 112,
    CX      = 113,
    DX      = 114

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
    "mov",
    "inc",
    "dec",
    "call",
    "ret",
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
