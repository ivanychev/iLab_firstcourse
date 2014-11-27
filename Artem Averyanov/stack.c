#include "my_stack.h"

int stack_ctor(struct stack_t* _this)
{
	ISNOTNULL( _this );
	_this->data = calloc(STACK_MAX_LENGTH, sizeof(double));
	_this->count = 0;
	ISNOTNULL(_this->data);
	assert(_this->data);
	return 0;

}

int stack_push(struct stack_t* _this, double value)
{
	ISNOTNULL(_this);
	if (_this->count < STACK_MAX_LENGTH)
	{
		_this->data[_this->count] = value;
		(_this->count)++;
		return 0;
	}
	else
	    return STACK_FULL;
}

int stack_pop(struct stack_t* _this, double* value)
{
	ISNOTNULL(_this);
	ISNOTNULL(value);
	if (_this->count > 0)
	{
		ISNOTNULL(_this->data);
		*value = _this->data[_this->count-1];
		(_this->count)--;
		return 0;
	}
	else
	    return STACK_EMPTY;
}

void stack_dtor(struct stack_t* _this)
{
	free(_this->data);
	_this->data = NULL;
	_this->count = -1;
}

int stack_dump(struct stack_t* _this)
{
	int i = 0;
	printf("stack %p\n", _this);
	printf("сounter: %d\n", _this->count);
	printf("stack_max_len: %d\n", STACK_MAX_LENGTH);
	if (_this->count > 0)
	{
		printf("stack_data:\n");
		for (i = 0; (i < _this->count); i++)
		{
			printf("\t%d:  %g\n", i, *(_this->data+i));
		}
	}
	return 0;
}

int is_stack_full(struct stack_t _this)
{
	if (_this.count > STACK_MAX_LENGTH) return 0;
	else return 1;
}

int is_stack_empty (struct stack_t _this)
{
	if (_this.count == 0) return 0;
	else return 1;
}

int stack_size(struct stack_t _this)
{
	return _this.count;
}

int is_stack_ok(struct stack_t _this)
{
	if ((_this.count < 0) || (_this.count > STACK_MAX_LENGTH)) return INVALID_COUNTER;
	else if (_this.data == NULL) return NULL_PTR;
	     else return 0;
}

void er(int er_numb)
{
	switch(er_numb)
	{
		case NULL_PTR:     printf("NULL ptr");        break;
		case STACK_FULL:   printf("stack is full");   break;
		case STACK_EMPTY:  printf("stack is empty");  break;
		//default: break;
	}
}

/*int main(int argc, char const *argv[])
{
	return 0;
}*/

int main()
{
	struct stack_t stack = {};
	double value_1 = 1500;
	
	er(stack_ctor(&stack));
	
	er(stack_push(&stack, 10));
	er(stack_push(&stack, 20));
	er(stack_push(&stack, 30));
	
	er(stack_dump(&stack));
	
    	er(stack_pop(&stack, &value_1));
	printf("%lg\n", value_1);
	
	er(stack_dump(&stack));
	stack_dtor(&stack);
	return 0;
}


/*
	TODO

	[COMPLETED]- Улучшить dump. Добавить вывод указателя и, собственно, того, что
	дампится стек
	[COMPLETED]- Исправить switch
	[COMPLETED]- Добавить методы is_full, is_empty, size, ok, 
	[COMPLETED]- Преамбулу в header
*/

