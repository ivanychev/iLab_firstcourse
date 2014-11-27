#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#define ISNOTNULL(_this) if (_this == NULL) {return NULL_PTR;}

const int STACK_MAX_LENGTH = 25;

//Stack
struct stack_t
{
	double* data;
	int count;
};

enum ERRORS
{
	FIRST_ERROR_NUMBER     = 1000,	
	NULL_PTR               = 1001,
	STACK_FULL             = 1002,
	STACK_EMPTY            = 1003,
	INVALID_COUNTER        = 1004,
	LAST_ERROR_NUMBER      = 1005,
};
