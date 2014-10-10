/**
    @file
    Program for solving quadratic equation.

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.1


*/

#include<stdio.h>
#include<math.h>
#include<assert.h>

const double POISON =  -13.666;
const int N_COEFF   =   3;
const int N_ROOTS   =   2;
const int INF_ROOTS =  -1;

/**
    Function quadratic solves quadratic equation(ax^2 + bx + c = 0)

    @param a  coefficient a
    @param b  coefficient b
    @param c  coefficient c
    @param x1 first root
    @param x2 second root

    @return count of roots(-1 then infinite root)

*/
int quadratic(double a, double b, double c, double* x1, double* x2);



int main()
{

    double a = POISON, b = POISON, c = POISON;
    double x1 = POISON, x2 = POISON;

    printf("This program solves quadratic equation.");
    printf("Write coefficients of quadratic equation(e.g a = 123 b = 321 c = 0.1)\n");

    while (!scanf("a = %lg b = %lg c = %lg", &a, &b, &c))
    {

        while (getchar() != '\n');
        printf("Write correct!\n");
    }


    int count_roots = quadratic(a, b, c, &x1, &x2);

    switch(count_roots)
    {

        case INF_ROOTS:
            printf("All real numbers");
            break;
        case 0:
            printf("No roots");
            break;
        case 1:
            printf("Count of roots: %d\nx = %lg", count_roots, x1);
            break;
        case 2:
            printf("Count of roots: %d\nx1 = %lg x2 = %lg", count_roots, x1, x2);
            break;

    }

    return 0;
}


int quadratic(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
                return INF_ROOTS;
            else
                return 0;

        }
        else
        {
            *x1 = - c/b;
            return 1;
        }
    }

    else
    {
        double discr = b*b - 4*a*c;
        if (discr < 0)
            return 0;
        else
        {
            if (discr == 0)
            {
                *x1 = - b / 2/a;
                return 1;
            }
            else
            {
                discr = sqrt(discr);
                *x1 = (- b + discr) / 2/a;
                *x2 = (- b - discr) / 2/a;
                return 2;

            }

        }

    }
}
