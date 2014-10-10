/**
    @file
    This program contains 10 function
    each of them solves one problem(A, B, C or D)
    from exam 2007.

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>


#define IN_LIMIT( A , B , I ) assert((( A ) <= ( I )) && (( I ) <= B))

const int YES = 1;
const int  NO = 0;
const int ERROR = 123321;

//===========================================================================

/**
    Variant 1 Problem C
    This function returns can you "weigh" number
    using weights = 1, 4, 4^2, 4^3 ...

    @param x number which we want weigh(0 < x < 2^31)

    @return const YES if we can weigh number, const NO if we can't do this

*/
int weighing(long x);

//===========================================================================

/**
    This function realize sieve of Eratosthenes

    @param primes   array where primes[i]=0 if prime and =1 if not
    @param    len   size of sieve

*/
int sieve_of_Eratosthenes(int primes[], int len);

/**
    Variant 2 Problem C
    This function find the Nth prime number

    @param amount_prime   number of prime number(number < 10000)

    @return Nth prime number

*/
int find_Nth_prime(const int amount_prime);

/**
    Variant 7 Problem C
    This function find primes by numbers

    @param array_amount_primes   array with numbers of primes
    @param             nPrimes   count of numbers
    @param              primes   array where write of primes

*/
int find_Nths_primes(const int numbers_of_primes[], const int nPrimes, int primes[]);

//===========================================================================

/**
    Variant 4 Problem B
    This function filter string - delete more than 1 spaces,
    change upper letter to lower and replace numbers to #

    @param str   string for filter

*/
int symbol_filter(char* str);

/**
    This function deletes symbol in n position

    @param str   string
    @param   n   position of deleting symbol

*/
int del_symbol(char* str, int n);

//===========================================================================

/**
    Variant 4 Problem C
    This function reverse words in string

    @param str   string

*/
int reverse_str(char str[]);

/**
    This function reverse one word(left, right) in string

    @param   str   string
    @param  left   start of the word in str
    @param right   end of the word in str

*/
int reverse_word(char str[], int left, int right);

/**
    This function swap 2 char variable

    @param a   first char
    @param b   second char
*/
int swap_char(char *a, char *b);

//===========================================================================

/**
    Variant 5 Problem A
    This function find sum of exponential series

    @param n count
    @param x variable of series
    @return sum of exponential series xn

*/
double sum_of_series_exp(int n, double x);

/**
    This function find factorial of number n

    @param n   number

    @return factorial

*/
long factorial(int n);

//===========================================================================

/**
    Variant 2 Problem B
    This function normalize sqrt(N) to a*sqrt(b), where a - maximum

    @param         n   number
    @param  overroot   overroot
    @param underroot   under root

*/
int normalize_sqrt(long num, long* overroot, long* underroot);

//===========================================================================

/**
    Variant 6 Problem D
    This function find number of decompositions to sum

    @param n first number
    @param k second number
    @return number of decompositions

*/
int nDecompositions_to_sum(const int n, const int k);

//===========================================================================

/**
    (2008)Variant 8 Problem D
    This function find sum of num1 and num2

    @param     num1   string with the first num
    @param len_num1   length of the first num
    @param     num2   string with the second num
    @param len_num2   length of the second num

    @return string with sum of num1 and num2

*/
char* long_arithmetics(char num1[], int len_num1, char num2[], int len_num2);

/**
    This function find maximum of 2 numbers

    @param a   number
    @param b   number
    @return maximum of a and b

*/
int max_int(int a, int b);

//===========================================================================

/**
    Variant 7 Problem D
    This function find all binary word

    @param  count_of_call   counter of writing in array_of_words
    @param           word   binary word
    @param            len   length of binary word
    @param  remaining_len   length of indefinite part of binary word
    @param array_of_words   array where write words

*/
int binary_word(int *count_of_call, int word[],
                int len, int remaining_len,
                int remaining_count_ones,
                int* array_of_words[]);
//===========================================================================
//===========================================================================
/**
    MAIN FUNCTION

    It has input processing and it calls functions

    @return 0 if OK

*/
int main()
{
    char c = '0';
    char* introduction = "This program can solve 10 problem.\n"
           "Write 0 if you want run problem \"weighing\"                  (2007 Var 1 Prob C)\n"
           "Write 1 if you want run problem \"the Nth prime number\"      (2007 Var 2 Prob C)\n"
           "Write 2 if you want run problem \"output primes by numbers\"  (2007 Var 7 Prob C)\n"
           "Write 3 if you want run problem \"turning words\"             (2007 Var 4 Prob C)\n"
           "Write 4 if you want run problem \"generating good word\"      (2007 Var 7 Prob D)\n"
           "Write 5 if you want run problem \"sum of exponential series\" (2007 Var 5 Prob A)\n"
           "Write 6 if you want run problem \"number of decompositions\"  (2007 Var 6 Prob D)\n"
           "Write 7 if you want run problem \"filter of symbols\"         (2007 Var 4 Prob B)\n"
           "Write 8 if you want run problem \"normalization of root\"     (2007 Var 2 Prob B)\n"
           "Write 9 if you want run problem \"sum of big numbers\"        (2008 Var 8 Prob D)\n"
           "Write -1 if you want exit\n";
    printf("%s", introduction);

    while((c = getchar()) != '-')
    {
        while (getchar() != '\n' );
        switch(c)
        {

        case '0':
            {
            printf("Write x number which we want weigh(0 < x < 2^31)\n");

            long a = 0;

            while (!scanf("%d", &a))
            {
                while(getchar() != '\n');
                printf("Write x number which we want weigh(0 < x < 2^31)\n");
            }

            printf((weighing(a) == YES)? "YES, you can weight it\n": "NO, you can't weight it\n");

            }
            break;

        case '1':
            {
            printf("Write number of primes(0 < number < 10000)\n");

            int number_of_prime = 0;

            while (!scanf("%d", &number_of_prime))
            {
                while(getchar() != '\n');
                printf("Incorrect! Write number of prime(0 < N < 10000)\n");
            }

            printf("%d\n", find_Nth_prime(number_of_prime));

            }
            break;

        case '2':
            {
            printf("Write amount numbers of primes(0 < amount < 10000)\n");

            int nPrimes = 0;

            while (!scanf("%d", &nPrimes))
            {
                while(getchar() != '\n');
                printf("Incorrect! Write amount numbers of primes(0 < amount < 10000)\n");
            }


            int* numbers_of_prime = (int*) calloc(nPrimes, sizeof(*numbers_of_prime));
            assert(numbers_of_prime);

            printf("Write %d numbers of primes(0 < number < 10000)\n", nPrimes);

            int i = 0;

            while(i < nPrimes)
            {
                while (!scanf("%d", &numbers_of_prime[i]))
                {
                    while(getchar() != '\n');
                    i = 0;
                    printf("Incorrect! Write %d number of prime(0 < N < 10000)\n", nPrimes);
                }
                i++;
            }

            int* primes = (int*) calloc(nPrimes, sizeof(*primes));
            assert(primes);

            find_Nths_primes(numbers_of_prime, nPrimes, primes);
            free(numbers_of_prime);

            for(i = 0; i < nPrimes; i++)    printf("%d ", primes[i]);
            free(primes);

            putchar('\n');


            }
            break;

        case '3':
            {
            const int MAX_LEN = 1000;

            printf("Write string that you want reverse\n");

            char* str = (char*) calloc(MAX_LEN, sizeof(*str));
            assert(str);

            int i = 0;

            while((str[i] = getchar()) != '\n') i++;

            str[i] = ' ';
            str[i+1] = '\n';

            reverse_str(str);

            printf("%s", str);

            free(str);
            }
            break;

        case '4':
            {
            const int MAX_WORDS = 1000;

            printf("Write length of binary words and amount of ones\n");

            int len = 0, amount_ones = 0;

            while(scanf("%d %d", &len, &amount_ones) != 2)
            {
                while(getchar() != '\n');
                printf("Incorrect! Write length of binary words and amount of ones\n(e.g. 4 2)");
            }

            int** array_of_words = (int**) calloc(MAX_WORDS, sizeof(*array_of_words));
            assert(array_of_words);

            int amount_words = 0;

            int* word1 = (int*) calloc(len, sizeof(*word1));
            assert(word1);
            word1[0] = 0;

            binary_word(&amount_words, word1, len, len-1, amount_ones,   array_of_words);
            free(word1);

            int* word2 = (int*) calloc(len, sizeof(*word2));
            assert(word2);
            word2[0] = 1;

            binary_word(&amount_words, word2, len, len-1, amount_ones-1, array_of_words);
            free(word2);

            for(int j = 0; j < amount_words; j++)
            {
                for (int l = 0; l < len; l++)   printf("%d", array_of_words[j][l]);
                free(array_of_words[j]);
                putchar('\n');
            }
            free(array_of_words);

            }
            break;

        case '5':
            {
            printf("Write count elements N and variable X(e.g. 6 3.2)\n");

            int n = 0;
            double x;

            while(scanf("%d %lg", &n, &x) != 2)
            {
                while(getchar() != '\n');
                printf("Incorrect! Write count elements N and variable X(e.g. 6 3.2)");
            }

            printf("%lg\n", sum_of_series_exp(n, x));

            }
            break;

        case '6':
            {
            printf("Write natural number\n");

            int num = 0;

            while(!scanf("%d", &num))
            {
                while(getchar() != '\n');
                printf("Incorrect! Write natural number\n");
            }

            printf("%d\n", nDecompositions_to_sum(num, num));

            }
            break;

        case '7':
            {
            const int MAX_LEN = 1000;

            printf("Write string that you want filter\n");


            char* str = (char*) calloc(MAX_LEN, sizeof(*str));
            assert(str);

            int i = 0;

            while((str[i] = getchar()) != '\n') i++;

            symbol_filter(str);

            printf("%s", str);

            free(str);

            }
            break;

        case '8':
            {
            printf("Write number, whose square root you want normalize\n");

            long number = 0;

            while(!scanf("%d", &number))
            {
                while(getchar() != '\n');
                printf("Incorrect! Write number, whose square root you want normalize\n");
            }

            long underroot = 0, overroot = 0;

            normalize_sqrt(number, &overroot, &underroot);

            printf("%d*sqrt(%d)\n", overroot, underroot);

            }
            break;

        case '9':
            {
            const int MAX_LEN = 1000;

            char* num1 = (char*) calloc(MAX_LEN, sizeof(*num1));
            assert(num1);

            char* num2 = (char*) calloc(MAX_LEN, sizeof(*num2));
            assert(num2);

            int len_num1 = 0, len_num2 = 0;

            while ((num1[len_num1] = getchar()) != '\n')    len_num1++;
            while ((num2[len_num2] = getchar()) != '\n')    len_num2++;

            printf("%s\n", long_arithmetics(num1, len_num1, num2, len_num2));

            free(num1);
            free(num2);

            }
            break;
        default:
            if (c != 'n') while (getchar() != '\n');
            break;
        }
        while (getchar() != '\n' );
        printf(introduction);

    }

    return 0;
}


// PROBLEM 0
int weighing(long x)
{
    IN_LIMIT(1, 2147483647, x);

    const int WEIGHT = 4;

    while (x > 1)
    {
        int mod = x % WEIGHT;
        switch(mod)
        {
        case 0:
            x /= WEIGHT;
            break;
        case 1:
            x--;
            x /= WEIGHT;
            break;
        case 2:
            return NO;
            break;
        case 3:
            x++;
            x /= WEIGHT;
            break;
        default:
            assert(NO);

        }

    }

    return YES;

}

// PROBLEM 1
int find_Nth_prime(const int number_of_prime)
{
    IN_LIMIT(1, 10000, number_of_prime);

    const int LEN_SIEVE = 110000; // magic number(maximum length of  sieve
                                  // of Eratosthenes for number of prime = 10000)
    int* primes = (int*) calloc(LEN_SIEVE, sizeof(primes));
    assert(primes);

    int count_of_primes = 0;

    sieve_of_Eratosthenes(primes, LEN_SIEVE);

    int i = 0;
    for (i=0; i < LEN_SIEVE; i++)
    {
        if (!primes[i]) count_of_primes++;
        if (count_of_primes == number_of_prime) break;

    }

    return i;

}

//USING BY PROBLEM 1
int sieve_of_Eratosthenes(int primes[], const int len)
{
    assert(primes);
    IN_LIMIT(1, 300000, len);

    primes[0] = primes[1] = 1;

    for (int i = 2; i < len; i++)
    {
        IN_LIMIT(2, len, i);
        primes[i] = 0;
    }

    int counter = 2;

    while (counter*counter < len)
    {
        for (int i = counter * counter; i < len; i += counter)
        {
            IN_LIMIT(0, len, i);
            primes[i] = 1;
        }

        counter++;

        while (primes[counter]) counter++;

    }

}

// PROBLEM 2
int find_Nths_primes(const int numbers_of_primes[],
                     const int nPrimes,
                     int primes[])
{
    assert(numbers_of_primes);
    assert(primes);

    for (int i = 0; i < nPrimes; i++)
    {
        IN_LIMIT(0, nPrimes, i);
        primes[i] = find_Nth_prime(numbers_of_primes[i]);

    }


}

//PROBLEM 3
int reverse_str(char str[])
{
    assert(str);

    int left = -1;

    for(int i = 0; str[i]; i++)
    {
        if ((left == -1) && isalnum(str[i])) left = i;
        if ((left != -1) && (!isalnum(str[i])))
        {
            reverse_word(str, left, i - 1);
            left = -1;
        }
    }

}

//USING BY PROBLEM 3
int reverse_word(char str[], int left, int right)
{
    assert(str);

    int len = strlen(str);

    for (int i = 0; i <= (right-left)/2; i++)
    {
        IN_LIMIT(0, len, i);
        swap_char(&str[right - i], &str[left + i]);
    }

}

//PROBLEM 4
int binary_word(int *count_of_call, int word[],
                 int len, int remaining_len,
                 int remaining_count_ones,
                 int* array_of_words[])
{
    assert(count_of_call);
    assert(word);
    assert(array_of_words);

    if (remaining_len == 0)
    {
            int* new_word = (int*) calloc(len, sizeof(*new_word));
            new_word = (int*) memcpy(new_word, word, len*sizeof(*word));
            assert(new_word);

            IN_LIMIT(0, 1000000, *count_of_call);
            array_of_words[*count_of_call] = new_word;
            *count_of_call += 1;
    }
    else
    {
        IN_LIMIT(0, len, len - remaining_len);
        if ((word[len - remaining_len - 1] == 1) || (remaining_count_ones == 0))
        {
            word[len - remaining_len] = 0;
            binary_word(count_of_call, word, len, (remaining_len-1), remaining_count_ones, array_of_words);
        }
        else
        {
            if ((remaining_len) == (remaining_count_ones * 2 - 1))
            {
                word[len - remaining_len] = 1;
                binary_word(count_of_call, word, len, (remaining_len-1), (remaining_count_ones-1), array_of_words);

            }
            else if ((remaining_len) > (remaining_count_ones * 2 - 1))
            {
                word[len - remaining_len] = 1;
                binary_word(count_of_call, word, len, (remaining_len-1), (remaining_count_ones-1), array_of_words);

                word[len - remaining_len] = 0;
                binary_word(count_of_call, word, len, (remaining_len-1), remaining_count_ones, array_of_words);

            }
        }
    }

}

//PROBLEM 5
double sum_of_series_exp(const int n, const double x)
{
    double sum = 1;

    for (int i = 1; i <= n; i++)    sum += pow(x, i) / factorial(i);

    return sum;

}

//USING BY PROBLEM 5
long factorial(int n)
{
    assert(n > 0);
    long factor = 1;

    while (n > 1)
    {
        factor *= n;
        n--;
    }

    return factor;
}

//PROBLEM 6
int nDecompositions_to_sum(const int n, const int k)
{
    if ((k == 1)||(n == 1))
        return 1;

    if ((k < 0)||(n < 0))
        return 0;

    return nDecompositions_to_sum(n - k, k) + nDecompositions_to_sum(n, k - 1);


}

//PROBLEM 7
int symbol_filter(char* str)
{
    assert(str);

    for(int i = 0; str[i]; i++)
    {
        if (isdigit(str[i]))    str[i] = '#';
        else if (isupper(str[i]))   str[i] = tolower(str[i]);
            else
            {
                if (ispunct(str[i]))    str[i] = ' ';

                if (isspace(str[i]) && isspace(str[i-1]))
                    {
                        del_symbol(str, i);
                        i--;
                    }
            }

    }

}

//USING BY PROBLEM 7
int del_symbol(char* str, int n)
{
    assert(str);
    int len = strlen(str);

    for(int i = n; i <= len; i++)
    {
        IN_LIMIT(n, len, i);
        str[i] = str[i+1];
    }
}

//USING BY PROBLEM 7
int swap_char(char *a, char *b)
{
    assert(a);
    assert(b);

    char tmp = *a;
    *a = *b;
    *b = tmp;

}

//PROBLEM 8
int normalize_sqrt(long num, long* overroot, long* underroot)
{
    IN_LIMIT(0, 100000000, num);
    assert(overroot);
    assert(underroot);

    *overroot  = 1;
    *underroot = num;
    long last = 0, nsqrt = (long) sqrt(num);

    for (long i = 2; i <= nsqrt; i++)
    {

        while(!(*underroot % i))
        {

            if (!last) {last = i; *underroot /= i;}
            else
            {
                    *overroot *= i;
                    *underroot /= i;
                    last = 0;

            }
        }
        if (last) {*underroot *= last; last = 0;}



    }
    return 0;

}

//PROBLEM 9
char* long_arithmetics(char num1[], int len_num1,
                       char num2[], int len_num2)
{
    assert(num1);
    assert(num2);

    char CHR_0 = '0';
    int len_sum =  max_int(len_num1, len_num2) + 1;

    char* sum = (char*) calloc(len_sum, sizeof(*sum));
    assert(sum);

    int remain = 0;
    int digit1 = 0;
    int digit2 = 0;

    for(int i = 0; i < len_sum; i++)
    {
        digit1 = (((len_num1 - i - 1) < 0)? 0 : (num1[len_num1 - i - 1] - CHR_0));
        digit2 = (((len_num2 - i - 1) < 0)? 0 : (num2[len_num2 - i - 1] - CHR_0));
        sum[len_sum - i - 1] = (digit1 + digit2 + remain) % 10 + CHR_0;
        remain = (digit1 + digit2 + remain) / 10;
    }

    if (sum[0] == '0') return (sum + sizeof(*sum));

    return sum;

}

//USING BY PROBLEM 9
int max_int(int a, int b)
{
    return ((a > b)? a : b);
}
