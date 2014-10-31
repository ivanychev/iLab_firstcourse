/* Игорь Соколов, 453 группа ФФКЭ, 1 курс.
Решение квадратного уравнения
Используемые функции:
-Ввод численных значений переменных
-Решение уравнения
-Исправленная версия
*/

#include <stdio.h>
#include <math.h>
#include <ASSERT.h>
#include <stddef.h>
#include <stdlib.h>
#include <float.h>

#define ASSERT(x) if (!(x)){\
	printf("File: %s\n" \
	"Function: %s\n " \
	"Line: %d\n" \
	"Contidion: %s\n" \
	"Message: Houston, we have a problem!\n", \
	__FILE__, \
	__FUNCTION__, \
	__LINE__, #x); \
	abort();\
}\

const int   INF_ROOT = -1;
const int   NO_ROOTS = 0;
const int   ONE_ROOT = 1;
const int   TWO_ROOTS = 2;

//RETURN INT
int Enter(double* a, double* b, double* c)          //Ввод численных значений коэффициентов
{
	//НУЖНО ТРИ ОТДЕЛЬНЫХ ПРОВЕРКИ
	ASSERT(a != NULL);
	ASSERT(b != NULL);
	ASSERT(c != NULL);
	printf("Hello, this programm can greatly compute the solution of the quadratic equation!\n");
	printf("Ax^2+Bx+C=0\n");
	printf("Enter A, B, C\n");
	//ПРОВЕРКА ВВОДА
	ASSERT(scanf("%lg %lg %lg", a, b, c) == 3);
	return 1;
}

//АНГЛИЙСКИЙ
int Solution(double a,
	double b,
	double c,
	double* root1,
	double* root2)
{
	//ДВА АССЕРТА
	ASSERT(root1 != NULL);
	ASSERT(root2 != NULL);
	if (a == 0)                                       //Решение линейного уравнения				
	{
		if ((b == 0) && (c == 0))	return INF_ROOT;
		else  if (b == 0)			return   NO_ROOTS;
		else					*root1 = (-c) / b;
		return   ONE_ROOT;
	}

	else                                            //Решение квадратного уравнения				 
	{
		double D = b * b - 4 * a * c;
		//	ПРОБЕЛЫ + ПОМЕНЯЙ IF
		if (D>(-DBL_EPSILON))
		{
			*root1 = (-b + sqrt(D)) / (2 * a);
			*root2 = (-b - sqrt(D)) / (2 * a);
			return TWO_ROOTS;
		}
		else return NO_ROOTS;
	}
}

int main()
{
	double a = 0, b = 0, c = 0, root1 = 0, root2 = 0;
	//проверка ввода
	ASSERT(Enter(&a, &b, &c));
	int Nimber_Roots = Solution(a, b, c, &root1, &root2);
	switch (Nimber_Roots)
	{
	case   INF_ROOT: printf("All real numbers are roots\n");				break;
	case   NO_ROOTS: printf("No roots\n");									break;
	case   ONE_ROOT: printf("X = %lg\n", root1);							break;
	case   TWO_ROOTS: printf("X[1] = %lg\nX[2] = %lg\n", root1, root2);		break;
	default: ASSERT((&root1 != NULL) || (&root1 != NULL&&root2 != NULL));	break;
	}
	return 0;
}

// правильно возвращать код выполнения функции

