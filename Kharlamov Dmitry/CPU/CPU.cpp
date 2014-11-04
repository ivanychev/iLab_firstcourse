/**
    @file
    This program is my realization stack CPU.
    It gets byte code files and execute it.
    Output - console. Logs - logs.txt

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.0
*/

#include "stack\stack.h"
#include "resources.h"
#include "CPU.h"
#include "commands.h"


#define ERRHANDLER if (__errnum) { errlog(__errnum, __FILE__, __LINE__); cpu_dump(_this); return __errnum; }

const int       FOREVER = 1;
const int CPU_STACK_MAX = 10000;

struct cpu_t_
{
    stack_t *stk;
    double ax;
    double bx;
    double cx;
    double dx;
    char* addr;

};

/**
    This function inputs byte code of instructions

    @param      code   pointer on array of byte code
    @param file_name   name of file to input

    @return number of error(0 if no error)
*/
int cpu_input_code(char** code, char* file_name)
{

    FILE* in_file = fopen(file_name, "rb");
    assert(in_file);

    void* buf = calloc(CODE_SIZE, 1);
    assert(buf);

    fread(buf, 1, CODE_SIZE, in_file);
    assert(buf);

    fclose(in_file);

    *code = (char*) buf;

    return 0;
}

/**
    This function exec byte code of instructions

    @param      code  array of byte code

    @return number of error(0 if no error)
*/
int cpu_run(char* addr_code)
{
    assert(addr_code);

    cpu_t* cpu = NULL;

    cpu_ctor(&cpu, CPU_STACK_MAX, addr_code);

    char* current_byte = addr_code;

    start_logging("logs.txt");


    int __errnum = 0;
    while(FOREVER)
    {
        int cmd = *current_byte;
        current_byte++;

        switch(cmd)
        {
        case PUSH:
            if(cpu_push(cpu, &current_byte)) printf("CPU CRASHED! PUSH HAVEN'T FULFILLED");
            break;

        case POP:
            if(cpu_pop(cpu, &current_byte)) printf("CPU CRASHED! POP HAVEN'T FULFILLED");
            break;

        case OK:
            if(cpu_ok(cpu)) printf("CPU CRASHED! CPU ISN'T OK");
            break;

        case DUMP:
            if(cpu_dump(cpu)) printf("CPU CRASHED! DUMP HAVEN'T FULFILLED");
            break;

        case ADD:
            if(cpu_add(cpu)) printf("CPU CRASHED! ADD HAVEN'T FULFILLED");
            break;

        case SUB:
            if(cpu_sub(cpu)) printf("CPU CRASHED! SUB HAVEN'T FULFILLED");
            break;

        case MUL:
            if(cpu_mul(cpu)) printf("CPU CRASHED! MUL HAVEN'T FULFILLED");
            break;

        case DIR:
            if(cpu_dir(cpu)) printf("CPU CRASHED! DIR HAVEN'T FULFILLED");
            break;

        case SIN:
            if(cpu_sin(cpu)) printf("CPU CRASHED! SIN HAVEN'T FULFILLED");
            break;

        case COS:
            if(cpu_cos(cpu)) printf("CPU CRASHED! COS HAVEN'T FULFILLED");
            break;

        case SQRT:
            if(cpu_sqrt(cpu)) printf("CPU CRASHED! SQRT HAVEN'T FULFILLED");
            break;

        case JA:
            if(cpu_ja(cpu, &current_byte)) printf("CPU CRASHED! JA HAVEN'T FULFILLED");
            break;

        case JAE:
            if(cpu_jae(cpu, &current_byte)) printf("CPU CRASHED! JAE HAVEN'T FULFILLED");
            break;

        case JB:
            if(cpu_jb(cpu, &current_byte)) printf("CPU CRASHED! JB HAVEN'T FULFILLED");
            break;

        case JBE:
            if(cpu_jbe(cpu, &current_byte)) printf("CPU CRASHED! JBE HAVEN'T FULFILLED");
            break;

        case JE:
            if(cpu_je(cpu, &current_byte)) printf("CPU CRASHED! JE HAVEN'T FULFILLED");
            break;

        case JNE:
            if(cpu_jne(cpu, &current_byte)) printf("CPU CRASHED! JNE HAVEN'T FULFILLED");
            break;

        case JMP:
            if(cpu_jmp(cpu, &current_byte)) printf("CPU CRASHED! JMP HAVEN'T FULFILLED");
            break;

        case OUT:
            if(cpu_out(cpu)) printf("CPU CRASHED! OUT HAVEN'T FULFILLED");
            break;

        case END:
            return 0;
            break;
        default:
        {
            fprintf(stderr, "ERROR! Unknown command at address %o. \n", (int)current_byte);
            return 1;
        }

        }

    }
    return 0;
}

int cpu_ctor(cpu_t** _this, int length, char* addr)
{
    int __errnum = 0;
    cpu_t* cpu = (cpu_t*) calloc(sizeof(cpu_t), 1);

    ISNOTNULL(cpu);
    assert(length > 0);

    __errnum = stack_Ctor(&(cpu->stk), length);

    if (__errnum)
        {
            errlog(__errnum, __FILE__, __LINE__);
            cpu_dump(*_this);
            return __errnum;
        }

    cpu->ax = 0.0;
    cpu->bx = 0.0;
    cpu->cx = 0.0;
    cpu->dx = 0.0;
    cpu->addr = addr;

    *_this = cpu;

    return 0;
}

int cpu_push(cpu_t* _this, char** ptr_current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    char* current_byte = *ptr_current_byte;

    if (*current_byte == NUM)
    {
        current_byte++;

        double a = *(double*)current_byte;

        __errnum = stack_Push(_this->stk, a);

        current_byte += sizeof(double);
    }
    else
    {
        if (*current_byte != REG) return ECPUPUSH;
        current_byte++;
        if (*current_byte == AX) __errnum = stack_Push(_this->stk, _this->ax);
        if (*current_byte == BX) __errnum = stack_Push(_this->stk, _this->bx);
        if (*current_byte == CX) __errnum = stack_Push(_this->stk, _this->cx);
        if (*current_byte == DX) __errnum = stack_Push(_this->stk, _this->dx);
        current_byte++;
    }

    ERRHANDLER;

    *ptr_current_byte = current_byte;
    return 0;
}

int cpu_pop(cpu_t* _this, char** ptr_current_byte)
{
    ISNOTNULL(_this);
    ISNOTNULL(ptr_current_byte);
    ISNOTNULL(*ptr_current_byte);
    int __errnum = 0;

    char* current_byte = *ptr_current_byte;

    if (*current_byte == AX) __errnum = stack_Pop(_this->stk, &(_this->ax));
    if (*current_byte == BX) __errnum = stack_Pop(_this->stk, &(_this->bx));
    if (*current_byte == CX) __errnum = stack_Pop(_this->stk, &(_this->cx));
    if (*current_byte == DX) __errnum = stack_Pop(_this->stk, &(_this->dx));

    ERRHANDLER;

    (*ptr_current_byte)++;

    return 0;
}

int cpu_ok(cpu_t* _this)
{
    ISNOTNULL(_this);
    ISNOTNULL(_this->addr);
    return stack_Ok(_this->stk);


    return 0;
}

int cpu_dump(cpu_t* _this)
{
    ISNOTNULL(_this);

    stack_Dump(_this->stk);

    fprintf(stderr, "\nax %lg\nbx %lg\ncx %lg\ndx %lg\n\n",
            _this->ax, _this->bx, _this->cx, _this->dx);


    if (!_this->addr) fprintf(stderr, "Invalid address to byte code\n");
    else for(char* ptr = _this->addr; *ptr != END; ptr++)
    {
        if ((ptr - _this->addr) > CODE_SIZE) break;
        int byte = *ptr;
        fprintf(stderr, "%02x ", byte);
    }
    fprintf(stderr, "\n\n");


}

int cpu_add(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, (a + b));

    ERRHANDLER;

    return 0;
}

int cpu_sub(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, (a - b));

    ERRHANDLER;

    return 0;

}

int cpu_mul(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, (a * b));

    ERRHANDLER;

    return 0;

}

int cpu_dir(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, (a / b));

    ERRHANDLER;

    return 0;

}

int cpu_sin(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, sin(a));

    ERRHANDLER;

    return 0;

}

int cpu_cos(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, cos(a));

    ERRHANDLER;

    return 0;

}

int cpu_sqrt(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, sqrt(a));

    ERRHANDLER;

    return 0;

}

int cpu_ja(cpu_t* _this, char** current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a > b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jae(cpu_t* _this, char** current_byte)
{

    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a >= b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jb(cpu_t* _this, char** current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a < b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jbe(cpu_t* _this, char** current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a <= b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_je(cpu_t* _this, char** current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a == b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jne(cpu_t* _this, char** current_byte)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    double b = 0.0;

    __errnum = stack_Pop(_this->stk, &b);

    ERRHANDLER;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    if (a > b) *current_byte = _this->addr + label;
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jmp(cpu_t* _this, char** current_byte)
{

    ISNOTNULL(_this);
    int __errnum = 0;

    int label = *(int*)(*current_byte);

    if (label < 0) __errnum = EJMPBADLABEL;

    ERRHANDLER;

    *current_byte = _this->addr + label;

    return 0;

}

int cpu_out(cpu_t* _this)
{
    ISNOTNULL(_this);
    int __errnum = 0;

    double a = 0.0;

    __errnum = stack_Pop(_this->stk, &a);

    ERRHANDLER;

    __errnum = stack_Push(_this->stk, a);

    ERRHANDLER;

    printf("%lg\n", a);

    return 0;
}

int cpu_end(cpu_t* _this)
{
    ISNOTNULL(_this);
    end_logging();
    return 0;
}
