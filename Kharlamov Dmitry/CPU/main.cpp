#include "stdlib.h"
#include "stdio.h"
#include "CPU.h"


int main(int arvc, char* argv[])
{
    char* code = NULL;

    if (arvc == 1) cpu_input_code(&code, "program.code");
    else cpu_input_code(&code, argv[1]);

    cpu_interface(code);

    free(code);


}
