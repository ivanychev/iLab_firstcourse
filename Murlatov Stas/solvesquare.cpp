/* 1) Мурлатов Станислав Юрьевич
2) группа 413
3) ФРТК
4) программа для подсчета корней квадратного уравнения.
5) V 1.1
6) Изменения: -использованны указатели
-вывод в отдельной функции
-исправленно сравнение с 0
-использован assert

*/
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

const   int ONE_ROOT = 0, 
            TWO_ROOT = 1, 
			INF_ROOT = 2,  
			NO__ROOT = 3;

#define IS_ZERO(x) (abs(x) < DBL_EPSILON)


void Print(int count_roots);
void Enter(double* a, double* b, double* c);
int Solution(double a, double b, double c, double* root1, double* root2);

int main()
{
	int i = 1;
	double a = 0, b = 0, c = 0;
	double x1 = 0, x2 = 0;
	while (i == 1)
	{

		Enter(&a, &b, &c);
		int count_roots = Solution(a, b, c, &x1, &x2);

		switch (count_roots)
		{
		case NO__ROOT:
			Print(count_roots);
			break;
		case ONE_ROOT:
			Print(count_roots);
			printf(" x= %lg \n", x1);
			break;
		case TWO_ROOT:
			Print(count_roots);
			printf("x1= %lg  x2= %lg \n", x1, x2);
			break;
		case INF_ROOT:
			Print(count_roots);
			break;
		default: assert(false);
		}




		printf("\n Restart- 1\n"
			"Close programm - 2\n"
			);
		scanf_s("%d", &i);
	}
	return 0;
}

void Print(int count_roots)
{
	char str_array[4][18] = { "\n One root  ", "\n Two roots ", "\n Infinity roots ", "\n No roots " };
	printf(" %s ", str_array[count_roots]);
}


void Enter(double* a, double* b, double* c)
{
	printf("  Program for solving the quadratic equation  \n");
	printf("  Enter the coefficients of the following form Ax^2+Bx+C=0  \n");
	printf("  Enter coefficient A  ");
	scanf_s("%lg", a);
	printf("  Enter coefficient B ");
	scanf_s("%lg", b);
	printf("  Enter coefficient C ");
	scanf_s("%lg", c);
}

int Solution(double a, double b, double c, double* root1, double* root2)
{
	assert(root1 != NULL);
	assert(root2 != NULL);
	assert(root1 != root2);

	double discr = 0;      // discr = discriminant(дискриминант)
	if (IS_ZERO(a) && IS_ZERO(b))
	{
		if IS_ZERO(c)
		{
			return INF_ROOT;
		}
		return NO__ROOT; // c данными коэфицентов невозможно составить уравнение

	}
	else if IS_ZERO(a)
	{
		*root1 = -c / b;
		return ONE_ROOT; // У уравнения только один корень 
	}
	else
	{
		discr = b * b - 4 * a  *  c;
		if (discr < 0)
		{
			return NO__ROOT; // У уравнения с данными коэфицентами нет решений 
		}
		else if (discr > 0)
		{
			*root1 = (-b + sqrt(discr)) / (2 * a);		//	discr_root = sqrt(discr);
			*root2 = (-b - sqrt(discr)) / (2 * a);
			return TWO_ROOT; // У данного уравнения 2 корня 
		}
		else {
			*root1 = -b / (2 * a);
			return ONE_ROOT; //У данного уравнения 1 корень
		}
	}

}