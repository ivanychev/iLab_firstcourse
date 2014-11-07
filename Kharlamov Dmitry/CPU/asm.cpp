#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

#include "commands.h"


#define SKIPSPACES while(*prog == ' ' || *prog == '\t' || *prog == '\n') prog++;
#define ISNOTNULL( ptr ) assert(("NULL POINTER",ptr));

const int ARG_MAX = 20;
const int REG_MAX = 3;
const int PROG_MAX = 20000;
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

int asmscanf(char** ptr_prog, char* cmd);

int translation(char* str_prog, char* ptr, labels_t* labels);

int htod(char* val);

int main(int argc, char* argv[])
{

    FILE* in = NULL;

    if (argc == 1) in = fopen("program.txt", "r");
    else           in = fopen(argv[1], "r");

    if(!in) assert(!"BAD FILE");

    fseek (in, 0, SEEK_END);
    int file_len = ftell(in);
    fseek(in, 0, SEEK_SET);

    char* str_prog = (char*) calloc(file_len, sizeof(*str_prog));
    ISNOTNULL(str_prog);

    fread(str_prog, 1, file_len, in);
    fclose(in);

    char* cpu_code = (char*) calloc(CODE_MAX, 1);

    labels_t labels;
    labels.counter = 0;

    //printf("%s\n", str_prog);

    int end_code = translation(str_prog, cpu_code, &labels);
    for(int j = 0; j < labels.counter; j++)
    {
        printf("%s %d\n", labels.labels[j].name, labels.labels[j].addr);
    }

    translation(str_prog, cpu_code, &labels);

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


    fwrite(cpu_code, sizeof(char), end_code - (int)cpu_code, out);
    free(cpu_code);

    fclose(out);
}


int labels_search(labels_t labels, char* name)
{
    for (int i = 0; i < labels.counter; i++)
        if (!strcmp(name, labels.labels[i].name)) return labels.labels[i].addr;



    return -1;
}

int asmscanf(char** ptr_prog, char* cmd)
{
    ISNOTNULL(ptr_prog);
    ISNOTNULL(*ptr_prog);
    ISNOTNULL(cmd);


    char* prog = *ptr_prog;

    SKIPSPACES;

    sscanf(prog, "%s", cmd);

    prog += strlen(cmd);

    *ptr_prog = prog;

    return 0;

}

int translation(char* prog, char* ptr, labels_t* ptr_labels)
{
    ISNOTNULL(prog);
    ISNOTNULL(ptr);
    ISNOTNULL(ptr_labels);

    labels_t labels = *ptr_labels;

    char* start_code = ptr;
    char cmd[LEN_CMD_MAX] = "";

    asmscanf(&prog, cmd);

    int i = BEGIN;
    while (i <= END)
    {
        if (!strcmp(cmd, S_CMD[i - BEGIN]))
        {
            //printf("%s\n", cmd);
            *ptr = i;
            ptr++;

            //if (i == END) break;
            //else if (i > END) assert(!"undefined command");

            if (i == PUSH)
            {
                //char* arg = (char*) calloc(ARG_MAX, sizeof(char));
                //ISNOTNULL(arg);
                char arg[ARG_MAX] = "";

                asmscanf(&prog, arg);



                if (!strcmp(arg, S_REG[0])) {*ptr = REG; ptr++; *ptr = AX; ptr++;}
                else
                if (!strcmp(arg, S_REG[1])) {*ptr = REG; ptr++; *ptr = BX; ptr++;}
                else
                if (!strcmp(arg, S_REG[2])) {*ptr = REG; ptr++; *ptr = CX; ptr++;}
                else
                if (!strcmp(arg, S_REG[3])) {*ptr = REG; ptr++; *ptr = DX; ptr++;}
                else
                {
                    *ptr = NUM;
                    ptr++;

                    double val = atof(arg);
                    //printf("%lg\n", val);

                    if (val == HUGE_VAL && errno == ERANGE)
                        assert(!"Value of push is too huge");

                    *(double*)ptr = val;
                    ptr += sizeof(double);

                }

                //free(arg);
            }

            if (i == POP)
            {
                //char* reg = (char*) calloc(REG_MAX, sizeof(char));
                //ISNOTNULL(reg);
                char reg[REG_MAX] = "";

                asmscanf(&prog, reg);

                if (!strcmp(reg, S_REG[0])) {*ptr = AX; ptr++;}
                if (!strcmp(reg, S_REG[1])) {*ptr = BX; ptr++;}
                if (!strcmp(reg, S_REG[2])) {*ptr = CX; ptr++;}
                if (!strcmp(reg, S_REG[3])) {*ptr = DX; ptr++;}

                //free(reg);
            }

            if ((JA <= i && i <= JMP) || (i == CALL))
            {
                //char* name = (char*) calloc(LABEL_NAME_MAX, sizeof(char));
                //ISNOTNULL(name);
                char name[LABEL_NAME_MAX] = "";

                asmscanf(&prog, name);

                int len = strlen(name);
                //printf("%s %d\n", name, labels_search(labels, name));

                *(int*)ptr = labels_search(labels, name);
                ptr += sizeof(int);
                //free(name);
            }

            if (i == MOV)
            {
                //char str[20] = "";


                char reg[REG_MAX] = "";
                asmscanf(&prog, reg);

                reg[strlen(reg) - 1] = '\0';

                if (!strcmp(reg, S_REG[0])) {*ptr = AX; ptr++;}
                if (!strcmp(reg, S_REG[1])) {*ptr = BX; ptr++;}
                if (!strcmp(reg, S_REG[2])) {*ptr = CX; ptr++;}
                if (!strcmp(reg, S_REG[3])) {*ptr = DX; ptr++;}


                char arg[ARG_MAX] = "";
                asmscanf(&prog, arg);


                char last_char = arg[strlen(arg) - 1];


                if (isdigit(last_char) || last_char == 'h')
                {
                    double val = 0;
                    if (last_char == 'h')
                    {
                        arg[strlen(arg) - 1] = '\0';
                        val = (double) htod(arg);

                    }
                    else val = atof(arg);

                    *ptr = NUM;
                    ptr++;

                    if (val == HUGE_VAL && errno == ERANGE)
                        assert(!"Value of push is too huge");

                    *(double*)ptr = val;
                    ptr += sizeof(double);
                }
                else
                {
                    *ptr = REG;
                    ptr++;


                    if (!strcmp(arg, S_REG[0])) {*ptr = AX; ptr++;}
                    else
                    if (!strcmp(arg, S_REG[1])) {*ptr = BX; ptr++;}
                    else
                    if (!strcmp(arg, S_REG[2])) {*ptr = CX; ptr++;}
                    else
                    if (!strcmp(arg, S_REG[3])) {*ptr = DX; ptr++;}
                    else
                    assert(!"BAD MOV, 2nd arg is bad.");

                }



            }

            if (i == INC || i == DEC)
            {
                while (*prog == ' ') prog++;
                if (*prog == '\n')
                {
                    *ptr = NOARG;
                    ptr++;
                }
                else
                {
                    *ptr = REG;
                    ptr++;

                    char reg[REG_MAX] = "";
                    asmscanf(&prog, reg);

                    if (!strcmp(reg, S_REG[0])) {*ptr = AX; ptr++;}
                    else
                    if (!strcmp(reg, S_REG[1])) {*ptr = BX; ptr++;}
                    else
                    if (!strcmp(reg, S_REG[2])) {*ptr = CX; ptr++;}
                    else
                    if (!strcmp(reg, S_REG[3])) {*ptr = DX; ptr++;}
                    else
                    assert(!"BAD MOV, 2nd arg is bad.");
                }

            }



            if (!*prog) break;
            asmscanf(&prog, cmd);
            i = BEGIN;
        }
        else i++;

        if(i > END)
        {
            int len = strlen(cmd) - 1;


            if (cmd[len] != ':') assert(!"unknown command!");

            cmd[len] = '\0';

            //char* name = (char*) calloc(LABEL_NAME_MAX, sizeof(char));
            //ISNOTNULL(name);
            //char name[LABEL_NAME_MAX] = "";

            //memcpy(name, cmd, (strlen(cmd) - 1));


            int label_num = labels_search(labels, cmd);

            if (label_num == -1)
            {
                strcpy(labels.labels[labels.counter].name, cmd);
                labels.labels[labels.counter].addr = (int)ptr - (int)start_code;
                labels.counter++;
            }

            if (!*prog) break;
            asmscanf(&prog, cmd);
            i = BEGIN;
        }



    }

    *ptr_labels = labels;

    return (int)ptr;
}

int htod(char* val)
{
    int dec = 0;
    while(*val)
    {

       dec = dec * 16 + (*val - '0') % 10;
       val++;
    }

    return dec;
}
