#include <stdio.h>
/**

Вариант 3
Задача C
*/


int main()
{
    char* c=new char;//our string variable

    int i=0,curri=0;//curri-for getchar,i-for calculations

    int length=0; // length of "word"

    do
    {
        c[curri]=getchar();


        if ((c[curri]!=EOF)  &&  ((c[curri]>='a'&&c[curri]<='z')||(c[curri]>='A'&&c[curri]<='Z')))
        {
            length++; //if it's a word,length variable increases
        }
        else
        {
            for (int j=i+length; j>i; j--)printf("%c",c[j-1]);    //if word ends,it is writing reverted
            i+=length;
            i++;
            length=0;
            if(c[curri]!='\n')printf("%c",c[curri]);
        }

        curri++;

    }
    while(c[curri-1]!='\n');  //loop ends after user use enter

    return 0;
}
