#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct cmd_t
{
    char* str;
    int num;
    double value;

};


int stack_interface(FILE* input_file);

int input_cmd(FILE* input_file, char* cmd);

int cmd_to_num(char* str_cmd);

#endif // IO_H_INCLUDED
