/**
    @file This program makes file with sorted by
    letters lines of poem "Evgeny Onegin".

    @author Dmitry Kharlamov, student of 1st course DREC MIPT.
    @version 1.1
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
/**
    This function find length of file in symbols

    @param f file, which length will find

    @return length

*/
long filelen(FILE* f);


/**
    This function find count of lines in array of chars

    @param text    array of chars

    @return count of lines

*/
long countLines(char* text);


/**
    This function using by qsort for compare 2 strings

    @param a    pointer to string
    @param b    pointer to string

*/

int compare(const void* a, const void* b);


/**
    This function input strings from file and
    make array of pointer to string

    @param nameFile    name of file to input
    @param   nLines    count of pointer to string

    @return  array of pointer to string

*/
char** inputFile(char* nameFile, int* nLines);

/**
    This function output sorted strings
    to file as encyclopedia
    !!!WORKING CORRECT ONLY WITH STRINGS ON RUSSIAN

    @param nameFile    name of file to output
    @param      txt    sorted array of pointer to string
    @param   nLines    count of pointer to string

*/
int outputFile(char* nameFile, char** txt, int nLines);



int main()
{
    setlocale(LC_CTYPE, "Rus");

    char* inFileName = "evgeny_onegin.txt";

    int nLines = 0;
<<<<<<< HEAD

    char** txt = inputFile(inFileName, &nLines);
    assert(txt);

    qsort(txt, nLines, sizeof(*txt), compare);

    char* outFileName = "encyclopedia.txt";

    outputFile(outFileName, txt, nLines);


    return 0;
}


char** inputFile(char* nameFile, int* nLines)
{
    assert(nameFile);

=======

    char** txt = inputFile(inFileName, &nLines);
    assert(txt);

    qsort(txt, nLines, sizeof(*txt), compare);

    char* outFileName = "encyclopedia.txt";

    outputFile(outFileName, txt, nLines);


    return 0;
}


char** inputFile(char* nameFile, int* nLines)
{
    assert(nameFile);

>>>>>>> 4f0705ef60bd700deddbf75d7f3318951b508425
    FILE* txtFile = fopen(nameFile, "r");
    assert(txtFile);

    long fSize = filelen(txtFile);

    char* buffer = (char*) calloc(fSize, sizeof(*buffer));
    assert(buffer);

    if (fread(buffer, sizeof(*buffer), fSize, txtFile) > fSize)  assert(("file read failed!", 0));

    fclose(txtFile);  txtFile = NULL;

    *nLines = countLines(buffer);

    char** txt = (char**) calloc(*nLines + 1, sizeof(*txt));
    assert(txt);

    txt[0] = buffer;
    int i = 1;

    for(char* buf_ptr = buffer+1; *buf_ptr; buf_ptr++)
    {
        if (*(buf_ptr - 1) == '\n')
        {
            txt[i] = buf_ptr;
            i++;
            *(buf_ptr - 1) = '\0';
        }
    }

    return txt;
}


int outputFile(char* nameFile, char** txt, int nLines)
{
    assert(txt);
    assert(nameFile);


    FILE* outputFile = fopen(nameFile, "w");
    assert(outputFile);

    for(int i = 1; i < nLines; i++)
    {
        if ('À' <= txt[i][0] && txt[i][0] <= 'ß')
        {

            if ((txt[i][0] > txt[i-1][0]) || (txt[i][0] == 'À' && txt[i-1][0] != 'À'))
                fprintf(outputFile, "\n==========%c==========\n\n", txt[i][0]);

            fprintf(outputFile,"%s\n", txt[i]);
        }


    }


    fflush(outputFile);
    fclose(outputFile);

}

int compare(const void* a, const void* b)
{
    assert(a);
    assert(b);

    return strcmp(*(char**)a, *(char**)b);

}

long countLines(char* text)
{
    assert(text);

    int counter = 0;

    for (char* ptr = text; *ptr; ptr++)
    {
        if (*ptr == '\n')   counter++;
        if ((*ptr != '\n') && (*(ptr+1) == '\0'))   counter++;
    }



    return counter;
}

long filelen(FILE* f)
{
    assert(f);

    long len = 0;

    fseek(f, 0, SEEK_END);
    len = ftell(f) - len;

    rewind (f);
    return len;
}
