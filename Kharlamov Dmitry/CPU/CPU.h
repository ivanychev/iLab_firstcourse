#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED


struct cpu_t_;

typedef cpu_t_ cpu_t;

int cpu_ctor(cpu_t** _this, int length, int code);


int cpu_input_code(char** code, char* file_name);

int cpu_interface(char* code);


//CPU COMMANDS

int cpu_push(cpu_t* _this, char** ptr_current_byte);

int cpu_pop( cpu_t* _this, char** ptr_current_byte);

int cpu_ok(cpu_t* _this);

int cpu_dump(cpu_t* _this);

int cpu_add(cpu_t* _this);

int cpu_sub(cpu_t* _this);

int cpu_mul(cpu_t* _this);

int cpu_dir(cpu_t* _this);

int cpu_sin(cpu_t* _this);

int cpu_cos(cpu_t* _this);

int cpu_sqrt(cpu_t* _this);

int cpu_ja( cpu_t* _this, char** current_byte);

int cpu_jae(cpu_t* _this, char** current_byte);

int cpu_jb( cpu_t* _this, char** current_byte);

int cpu_jbe(cpu_t* _this, char** current_byte);

int cpu_je( cpu_t* _this, char** current_byte);

int cpu_jne(cpu_t* _this, char** current_byte);

int cpu_jmp(cpu_t* _this, char** current_byte);

int cpu_out(cpu_t* _this);

int cpu_end(cpu_t* _this);

#endif // CPU_H_INCLUDED
