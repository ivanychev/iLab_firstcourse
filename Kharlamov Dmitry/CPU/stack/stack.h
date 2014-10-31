#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "../resources.h"
#include "../errors.h"

#define ISOKSTK( stack ) if (stack_Ok(stack)) return stack_Ok(stack);
#define ISNOTNULL( ptr ) if (!ptr) return ENULLPTR;
#define ISCNTINLIM( stack ) if (!(0 <= stack->counter && stack->counter < stack->len)) return ECNTOUTLIM;
#define ISLENINLIM( stack ) if (!(0 <= stack->len && stack->len < MAX_STACK)) return ELENOUTLIM;

#define OK( errnum, stack ) if(errnum) { error_processing(stack, errnum); assert(0); }


//STACK!!!
struct stack_t_;

typedef stack_t_ stack_t;

//=======INIT FUNTIONS FOR MANIPULATE STACK============

int stack_Ctor(stack_t** _this, int length);

int stack_Push(stack_t* _this, double value);

int stack_Pop(stack_t* _this, double* value);

int stack_Ok(stack_t* _this);

int stack_Print(stack_t* _this);

int stack_Dump(stack_t* _this);

int stack_Dtor(stack_t* _this);

int error_processing(stack_t* _this, int errnum);

int start_logging(char* log_file);

int end_logging();

#endif // STACK_H_INCLUDED
