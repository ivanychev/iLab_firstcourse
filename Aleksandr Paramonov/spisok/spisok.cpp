#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
int WORDLENGTH=100;
typedef char* data_t;
enum consts
{
    OK,
    NO_LIST,
    CANT_GO,
    WRONG
};

struct ListElem_t
{
    data_t data;
    ListElem_t* last;
    ListElem_t* next;
};
struct List
{
    ListElem_t* current;
    ListElem_t* first;
    int amount;
};
int listok(List* L);
int list_ctor(List* L)
{
    assert(L);
    L->first = (ListElem_t*) calloc (1, sizeof(ListElem_t));
//    L->first->data=(data_t) calloc (10, sizeof(char));
    assert(L->first);
    L->first->last=NULL;
    L->first->next=NULL;
    //L->first->data="1";
    L->current=L->first;
    L->amount=0;
    return 0;
}

int gotofirst(List* L)
{
    assert(L);
    if (L->first==NULL)return NO_LIST;
    L->current=L->first;
    return OK;
}

int gotonext(List* L)
{
    assert(L);
    if (L->current->next!=NULL)
    {
        L->current=L->current->next;
        return OK;
    }
    return CANT_GO;
}

int gotolast(List* L)
{
    if (listok(L)!=OK)return WRONG;
    if (L->current->last!=NULL)
    {
        L->current=L->current->last;
        return OK;
    }
    return CANT_GO;
}


int input(List* L,data_t value) //create element on the right side and move on it's position
{
    assert(L);
    if (L->current==NULL)return NO_LIST;
    ListElem_t* buffer=(ListElem_t*) calloc (1, sizeof(ListElem_t));
    assert(buffer);

    if (L->current->next==NULL)
    {

        buffer->next=NULL;
        buffer->last=L->current;
        L->current->next=buffer;
    }
    else
    {
        buffer->next=L->current->next;
        buffer->last=L->current;
        L->current->next->last=buffer;
        L->current->next=buffer;
    }
    (L->current->next->data)=value;
    L->amount++;
    gotonext(L);
    return OK;
}

int deleteelem(List* L)
{
    assert(L);
    if (L->current!=L->first)
    {
        if (L->current->next!=NULL)
            L->current->next->last=L->current->last;
        L->current->last->next=L->current->next;
        L->current=L->current->last;
        L->amount--;
        return OK;
    }
}

int list_dtor(List* L)
{
    if (listok(L)!=OK)return WRONG;
    return OK;
}

int readfromfile(FILE *F,List* L)
{
//if (listok(L)!=OK)return WRONG;
    assert(F);
//gotofirst(L);
    char* buf=(char*)calloc(WORDLENGTH,sizeof(char));
    if (fscanf(F,"%s",buf)!=EOF)
    {
        //printf("%s ", buf);
        input(L,buf);
    }
    return OK;
}
void dumplist(List* L)
{
    printf("_______________________DUMP________________________\n\n");
    assert(L);
    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        printf("%20s  %p\n",L->current->data,L->current);
    }
    printf("amount:%d\n\n_______________________DUMP________________________\n\n\n",L->amount);
}



int listcontainsthis(List* L,data_t data)
{

    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        if (strcmp(L->current->data,data)==0)  return 1;
    }
    return 0;
}

int listok(List* L)
{
    if (L==NULL)
    {
        printf("INCORRECT POINTER TO THE LIST,LOOKS LIKE LIST DOESNT EXIST!");
        return NO_LIST;
    }
    if (L->first==NULL)
    {
        printf("INCORRECT POINTER TO THE FIRST ELEMENT!");
        return WRONG;
    }
    gotofirst(L);
    int amount=0;
    while (L->current->next!=NULL)
    {
        gotonext(L);
        amount++;
    }
    if (amount!=L->amount)
    {
        printf("WRONG ELEMENT AMOUNT %d %d",amount,L->amount);
        return WRONG;
    }
    return OK;
}

int gethash(data_t data,int functionnumber)
{
    if (functionnumber==1)return 1;
    //printf("%d\n",data[0]%101);
    if (functionnumber==2)return abs((data[0])%101);
    if (functionnumber==3)return strlen(data)%101;
    if (functionnumber==4)
    {
        int sum=0;
        for (int i=0; i<strlen(data); i++)
        {
            sum+=abs(data[i]);
        }

        return sum%101;
    }
}

void hasher(List* L,List* H[101],int functionnumber)
{
    assert(L);
    assert(H);
    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        if(listcontainsthis(H[gethash(L->current->data,functionnumber)],L->current->data)==0)
        {
            input(H[gethash(L->current->data,functionnumber)],L->current->data);   //printf("%d\n",gethash(L->current->data,functionnumber));
        }
    }
}

int main()
{
    List* L;
    List* Hash[101];
    for(int i=0; i<101; i++)
    {
        Hash[i]=(List*) calloc (1, sizeof(List));
        list_ctor(Hash[i]);
    }
    L=(List*) calloc (1, sizeof(List));
    list_ctor(L);
    FILE* F;
    F=fopen("1.txt","r");
    assert(F);
    while(!feof(F))
    {
        readfromfile(F,L);
    }



    hasher(L,Hash,4);



    for (int i=0; i<101; i++)printf("i=%5d  %d\n",i,Hash[i]->amount);


}
