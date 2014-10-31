#include "stack\stack.h"
#include "resources.h"
#include "CPU.h"
//#include "errors.h"
#include "commands.h"

struct cpu_t_
{
    stack_t *stk;
    double ax;
    double bx;
    double cx;
    double dx;
    int code;

};

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

int cpu_interface(char* code)
{
    cpu_t original_cpu;
    cpu_t* cpu = &original_cpu;

    cpu_ctor(&cpu, 20, (int)code);

    char* current_byte = code;



    start_logging("logs.txt");

    while(1)
    {
        int cmd = *current_byte;
        current_byte++;

        switch(cmd)
        {
        case PUSH:
            cpu_push(cpu, &current_byte);
            break;

        case POP:
            cpu_pop(cpu, &current_byte);
            break;

        case OK:
            cpu_ok(cpu);
            break;

        case DUMP:
            cpu_dump(cpu);
            break;

        case ADD:
            cpu_add(cpu);
            break;

        case SUB:
            cpu_sub(cpu);
            break;

        case MUL:
            cpu_mul(cpu);
            break;

        case DIR:
            cpu_dir(cpu);
            break;

        case SIN:
            cpu_sin(cpu);
            break;

        case COS:
            cpu_cos(cpu);
            break;

        case SQRT:
            cpu_sqrt(cpu);
            break;

        case JA:
            cpu_ja(cpu, &current_byte);
            break;

        case JAE:
            cpu_jae(cpu, &current_byte);
            break;

        case JB:
            cpu_jb(cpu, &current_byte);
            break;

        case JBE:
            cpu_jbe(cpu, &current_byte);
            break;

        case JE:
            cpu_je(cpu, &current_byte);
            break;

        case JNE:
            cpu_jne(cpu, &current_byte);
            break;

        case JMP:
            cpu_jmp(cpu, &current_byte);
            break;

        case OUT:
            cpu_out(cpu);
            break;

        case END:
            return 0;
            break;
        default:
        {
            printf("NO\n");
            return 0;
        }


        }

    }
    return 0;
}

int cmd(int cmd, char** ptr_current_byte)
{
    char* current_byte = *ptr_current_byte;




    *ptr_current_byte = current_byte;
    return 0;
}



int cpu_ctor(cpu_t** _this, int length, int code)
{
    cpu_t* cpu = *_this;
    assert(length > 0);


    stack_Ctor(&(cpu->stk), length);

    cpu->ax = 0.0;
    cpu->bx = 0.0;
    cpu->cx = 0.0;
    cpu->dx = 0.0;
    cpu->code = code;

    *_this = cpu;

    return 0;
}

int cpu_push(cpu_t* _this, char** ptr_current_byte)
{
    char* current_byte = *ptr_current_byte;

    if (*current_byte == NUM)
    {
        current_byte++;

        double a = *(double*)current_byte;

        OK(stack_Push(_this->stk, a), _this->stk);

        current_byte += sizeof(double);
    }
    else
    {
        current_byte++;
        if (*current_byte == AX) stack_Push(_this->stk, _this->ax);
        if (*current_byte == BX) stack_Push(_this->stk, _this->bx);
        if (*current_byte == CX) stack_Push(_this->stk, _this->cx);
        if (*current_byte == DX) stack_Push(_this->stk, _this->dx);
        current_byte++;
    }

    *ptr_current_byte = current_byte;
    return 0;
}

int cpu_pop(cpu_t* _this, char** ptr_current_byte)
{
    char* current_byte = *ptr_current_byte;

    if (*current_byte == AX) stack_Pop(_this->stk, &(_this->ax));
    if (*current_byte == BX) stack_Pop(_this->stk, &(_this->bx));
    if (*current_byte == CX) stack_Pop(_this->stk, &(_this->cx));
    if (*current_byte == DX) stack_Pop(_this->stk, &(_this->dx));

    (*ptr_current_byte)++;

    return 0;
}

int cpu_ok(cpu_t* _this)
{
    if(!_this) return ENULLPTR;
    return stack_Ok(_this->stk);
    return 0;
}

int cpu_dump(cpu_t* _this)
{
    start_logging("logs.txt");

    stack_Dump(_this->stk);

    fprintf(stderr, "\nax %lg\nbx %lg\ncx %lg\ndx %lg\n\n",
            _this->ax, _this->bx, _this->cx, _this->dx);


}

int cpu_add(cpu_t* _this)
{
    double a, b;
    OK(stack_Pop(_this->stk, &a), _this->stk);
    OK(stack_Pop(_this->stk, &b), _this->stk);
    OK(stack_Push(_this->stk, (a + b)), _this->stk);

    return 0;
}

int cpu_sub(cpu_t* _this)
{
    double a, b;
    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    stack_Push(_this->stk, (a - b));

    return 0;

}

int cpu_mul(cpu_t* _this)
{
    double a, b;
    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    stack_Push(_this->stk, (a * b));

    return 0;

}

int cpu_dir(cpu_t* _this)
{
    double a, b;
    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    stack_Push(_this->stk, a / b);

    return 0;

}

int cpu_sin(cpu_t* _this)
{
    double a;
    stack_Pop(_this->stk, &a);

    stack_Push(_this->stk, sin(a));

    return 0;

}

int cpu_cos(cpu_t* _this)
{
    double a;
    stack_Pop(_this->stk, &a);

    stack_Push(_this->stk, cos(a));

    return 0;

}

int cpu_sqrt(cpu_t* _this)
{
    double a;
    stack_Pop(_this->stk, &a);

    stack_Push(_this->stk, sqrt(a));

    return 0;

}

int cpu_ja(cpu_t* _this, char** current_byte)
{
    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    //stack_Push(_this->stk, a);
    //stack_Push(_this->stk, b);

    if (a > b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jae(cpu_t* _this, char** current_byte)
{

    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    if (a >= b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jb(cpu_t* _this, char** current_byte)
{
    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    if (a < b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jbe(cpu_t* _this, char** current_byte)
{
    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    if (a <= b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_je(cpu_t* _this, char** current_byte)
{
    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    if (a == b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jne(cpu_t* _this, char** current_byte)
{
    double a, b;

    stack_Pop(_this->stk, &a);
    stack_Pop(_this->stk, &b);

    if (a != b) *current_byte = (char*)_this->code + *(int*)(*current_byte);
    else *current_byte += sizeof(int);

    return 0;

}

int cpu_jmp(cpu_t* _this, char** current_byte)
{

    *current_byte = *current_byte = (char*)_this->code + *(int*)(*current_byte);
    return 0;

}

int cpu_out(cpu_t* _this)
{
    double a;
    stack_Pop(_this->stk, &a);

    stack_Push(_this->stk, a);

    printf("%lg\n", a);

    return 0;
}

int cpu_end(cpu_t* _this)
{
    end_logging();
    return 0;
}
