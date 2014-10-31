#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "commands.h"


const int CODE_MAX = 16384;
const int LABEL_MAX = 30;
const int LABEL_NAME_MAX = 20;
const int LEN_CMD_MAX = 8;

const char ASM_FILE_EXTENSION[] = "code";

struct label_t
{
    char name[LABEL_NAME_MAX];
    int addr;
};

struct labels_t
{
    label_t labels[LABEL_MAX];
    int counter;
};

int labels_search(labels_t labels, char* name);

int main(int argc, char* argv[])
{

    char cmd[LEN_CMD_MAX] = "";

    void* cpu_code = calloc(CODE_MAX, 1);

    char* ptr;

    labels_t labels;
    labels.counter = 0;
    int twice = 2;

    while(twice)
    {
    FILE* in = NULL;
    if (argc == 1) in = fopen("program.txt", "r");
    else           in = fopen(argv[1], "r");

    if(!in) assert(!"BAD FILE");

    ptr = (char*) cpu_code;

    fscanf(in, "%s", cmd);

    int i = BEGIN;
    while (i <= END)
    {
        if (!strcmp(cmd, S_CMD[i - BEGIN]))
        {

            *ptr = i;
            ptr++;

            if (i == END) break;
            else if (i > END) assert(!"undefined command");

            if (i == PUSH)
            {
                double val = 0;
                if (fscanf(in, "%lg", &val))
                {
                    *ptr = NUM;
                    ptr++;
                    *(double*)ptr = val;
                    ptr += sizeof(double);


                }

                else
                {
                    *ptr = REG;
                    ptr++;
                    char reg[5] = "";
                    fscanf(in, "%s", reg);
                    if (!strcmp(reg, S_REG[0])) {*ptr = AX; ptr++;}
                    if (!strcmp(reg, S_REG[1])) {*ptr = BX; ptr++;}
                    if (!strcmp(reg, S_REG[2])) {*ptr = CX; ptr++;}
                    if (!strcmp(reg, S_REG[3])) {*ptr = DX; ptr++;}

                }

            }

            if (i == POP)
            {
                char reg[5] = "";
                fscanf(in, "%s", reg);
                if (!strcmp(reg, S_REG[0])) {*ptr = AX; ptr++;}
                if (!strcmp(reg, S_REG[1])) {*ptr = BX; ptr++;}
                if (!strcmp(reg, S_REG[2])) {*ptr = CX; ptr++;}
                if (!strcmp(reg, S_REG[3])) {*ptr = DX; ptr++;}


            }

            if (JA <= i && i <= JMP)
            {
                int num = 0;
                char name[LABEL_NAME_MAX] = "";

                fscanf(in, "%s", &name);

                int len = strlen(name);

                *(int*)ptr = labels_search(labels, name);
                ptr += sizeof(int);
            }

            fscanf(in, "%s", cmd);
            i = BEGIN;
        }
        else i++;
        if(i > END)
        {
            int len = strlen(cmd) - 1;
            if (cmd[len] != ':') assert(!"unknown command!");

            char name[LABEL_NAME_MAX] = "";
            memcpy(name, cmd, (strlen(cmd) - 1));



            int label_num = labels_search(labels, name);

            if (label_num == -1)
            {
                strcpy(labels.labels[labels.counter].name, name);
                labels.labels[labels.counter].addr = (int)ptr - (int)cpu_code;
                labels.counter++;
            }

            fscanf(in, "%s", cmd);
            i = BEGIN;
        }

    }
    fclose(in);

    twice--;
    }

    FILE* out = NULL;

    if (argc == 1) out = fopen("program.code", "wb");
    else
    {
        char asm_name[40];
        int len = strlen(argv[1]) - 3;

        memcpy(asm_name, argv[1], len);

        memcpy((asm_name+len), ASM_FILE_EXTENSION, strlen(ASM_FILE_EXTENSION));

        out = fopen(asm_name, "wb");
    }


    fwrite(cpu_code, sizeof(char), (int)ptr - (int)cpu_code, out);
    free(cpu_code);

    fclose(out);
}


int labels_search(labels_t labels, char* name)
{
    for (int i = 0; i < labels.counter; i++)
        if (!strcmp(name, labels.labels[i].name)) return labels.labels[i].addr;



    return -1;
}

