#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

const int INF_ROOT   = -1;
      int NO_ROOT    = 0;
      int ONE_ROOT   = 1;
      int TWO_ROOT   = 2;

bool is_zero(double x)
{
	
	if (abs(x) < DBL_EPSILON)
		return true;
	else
		return false;
}

int solvesquare(double coeff_1  = 0,
                double coeff_2  = 0,
                double coeff_3  = 0,
                double* root_1  = 0,
                double* root_2  = 0)
{
	double     discr    = 0,
               r_discr  = 0;
	
	if (is_zero(coeff_1))
		if (is_zero(coeff_2))
			if (is_zero(coeff_3)) return INF_ROOT;
			else return NO_ROOT;
		else
		{
			*root_1 = -coeff_3/coeff_2;
			return ONE_ROOT;
		}
	else
	{
		discr = coeff_2*coeff_2 -4*coeff_1*coeff_3;  //discr - Discriminant
		if (is_zero(discr)) 
		{
			*root_1 = -coeff_2/(2*coeff_1);
			return ONE_ROOT;
		}
		else
			if (discr < 0)
				return NO_ROOT;
			else
			{
				r_discr = sqrt(discr);
				*root_1 = (-coeff_2 - r_discr)/(2*coeff_1);
				*root_2 = (-coeff_2 + r_discr)/(2*coeff_1);
				return TWO_ROOT;
			}
	}
}





int main()
{
	double coeff_1  = 0,
	       coeff_2  = 0,
	       coeff_3  = 0,
	       root_1   = 0,
	       root_2   = 0;
	int a;
	
	scanf("%lg %lg %lg", &coeff_1, &coeff_2, &coeff_3);
	a = solvesquare(coeff_1, coeff_2, coeff_3, &root_1, &root_2);
	switch(a)
	case ONE_ROOT: printf("x = %f", root_1);                    break;
	case TWO_ROOT: printf("x1 = %f x2 = %f", root_1, root_2);   break;
	case INF_ROOT: printf("INF ROOT");                          break;
	case NO_ROOT:  printf("NO ROOT");                           break;
	
	return 0;
}

/*
TODO
	-	ИНИЦИАЛИЗИРОВАТЬ ПЕРЕМЕННЫЕ       || COMPLETED ||
	-	SWITCH BITCH!                     || COMPLETED ||
	-	Убрать лишние фигурные скобки     || COMPLETED ||



*/
