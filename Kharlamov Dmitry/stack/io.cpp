#include "io.h"


int const MAX_LEN_CMD = 15;

int stack_interface(FILE* input_file)
{
    cms_t cmd = {};
    char* cmd.str = (char*) calloc(sizeof(*str_cmd), MAX_LEN_CMD);

    if (!cmd.str) return 1;

    while("INFINITE LOOP")
    {
        input_cmd(input_file, cmd);
        int num_cmd = cmd_to_num(cmd);
        if (process_cmd(cmd_num)) break;
    }

    free(str_cmd);
    return 0;
}



int input_cmd(FILE* input_file, cmd_t cmd)
{


    for(int i = 0; i < MAX_LEN_CMD; i++) cmd[i] = '\0';
    int i = 0;
    while (i < MAX_LEN_CMD && (cmd[i] = tolower(fgetc(input_file))) != '\n') i++;

    retrun 0;
}


