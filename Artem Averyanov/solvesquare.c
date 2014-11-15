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
	{
		return true;
	}
	else
	{
		return false;
	}
}

int solvesquare(double coeff_1,
                double coeff_2,
                double coeff_3,
                double* root_1,
                double* root_2)
{
	double discr    = 0,
               r_discr  = 0;
	
	if (is_zero(coeff_1))
	{
		if (is_zero(coeff_2))
		{
			if (is_zero(coeff_3))
			{
				return INF_ROOT;
			}
			else
			{
				return NO_ROOT;
			}
		}
		else
		{
			*root_1 = -coeff_3/coeff_2;
			return ONE_ROOT;
		}
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
		{
			if (discr < 0)
			{
				return NO_ROOT;
			}
			else
			{
				r_discr = sqrt(discr);
				*root_1 = (-coeff_2 - r_discr)/(2*coeff_1);
				*root_2 = (-coeff_2 + r_discr)/(2*coeff_1);
				return TWO_ROOT;
			}
		}
	}
}





int main()
{
	double coeff_1,
	       coeff_2,
	       coeff_3,
	       root_1,
	       root_2;
	int a;
	
	scanf("%lg %lg %lg", &coeff_1, &coeff_2, &coeff_3);
	a = solvesquare(coeff_1, coeff_2, coeff_3, &root_1, &root_2);
	if (a == ONE_ROOT)
	{
		printf("x = %f", root_1);
	}
	if (a == TWO_ROOT)
	{
		printf("x1 = %f x2 = %f", root_1, root_2);
	}
	if (a == INF_ROOT)
	{
		printf("INF ROOT");
	}
	if (a == NO_ROOT)
	{
		printf("NO ROOT");
	}
	
	return 0;
}

/*
TODO
	-	ИНИЦИАЛИЗИРОВАТЬ ПЕРЕМЕННЫЕ
	-	SWITCH BITCH!
	-	Убрать лишние фигурные скобки



*/