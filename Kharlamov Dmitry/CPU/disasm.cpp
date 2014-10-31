#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "commands.h"

const int CODE_MAX = 16384;
const int LABEL_MAX = 30;
const int LABEL_NAME_MAX = 20;
const int LEN_CMD_MAX = 8;

int main(int argc, char* argv[])
{
    FILE* in = NULL;
    if (argc == 1) in = fopen("program.code", "rw");
    else           in = fopen(argv[1], "rw");

    if(!in) assert(!"BAD file!");

    void* buf = calloc(CODE_MAX, 1);

    fread(buf, 1, CODE_MAX, in);

    fclose(in);

    char* ptr = (char*) buf;


    FILE* out = fopen("disasm.txt", "w");

    int i = *ptr;
    ptr++;
    while (i != END)
    {
        fprintf(out, "%s", S_CMD[i - BEGIN]);

        if (i == PUSH)
        {
            if (*ptr == NUM)
            {
                ptr++;
                fprintf(out, " %lg", *(double*)ptr);
                ptr += sizeof(double);
            }
            else
            {
                ptr++;
                fprintf(out, " %s", S_REG[*ptr - AX]);
                ptr++;
            }
        }

        if (i == POP)
        {
            fprintf(out, " %s", S_REG[*ptr - AX]);
            ptr++;
        }


        if (JA <= i && i <= JMP)
        {
               fprintf(out, " %d", *(int*)ptr);

               ptr += sizeof(int);
        }


        fprintf(out, "\n");

        i = *ptr;
        ptr++;

    }
    fprintf(out, "end\n");
    fclose(out);

    free(buf);
}

