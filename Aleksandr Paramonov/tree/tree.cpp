#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
int WORDLENGTH=100;
typedef char* data_t;
enum constants
{
    OK,
    NO_TREE,
    CANT_GO,
    WRONG
};

struct TreeElem_t
{
    data_t data;
    TreeElem_t* last;
    TreeElem_t* left;
    TreeElem_t* right;
};

struct Tree
{
    TreeElem_t* current;
    TreeElem_t* first;
    int amount;
};

int tree_ctor(Tree* T,data_t data)
{
    assert(T);
    T->first = (TreeElem_t*) calloc (1, sizeof(TreeElem_t));

    assert(T->first);
    T->first->last=NULL;
    T->first->left=NULL;
    T->first->right=NULL;
    T->first->data=data;
    T->current=T->first;
    T->amount=0;
    return 0;


}

int tree_add_left(Tree* T,data_t data)
{
    assert(T);
    TreeElem_t* buffer=(TreeElem_t*) calloc (1, sizeof(TreeElem_t));
    assert(buffer);
    buffer->left=NULL;
    buffer->right=NULL;
    buffer->last=T->current;
    T->current->left=buffer;
    T->current->left->data=data;
    T->current->left->last=T->current;
    T->current=T->current->left;
    return OK;
}

int tree_add_right(Tree* T,data_t data)
{
    assert(T);
    TreeElem_t* buffer=(TreeElem_t*) calloc (1, sizeof(TreeElem_t));
    assert(buffer);
    buffer->left=NULL;
    buffer->right=NULL;
    buffer->last=T->current;
    T->current->right=buffer;
    T->current->right->data=data;
    T->current->right->last=T->current;
    T->current=T->current->right;
    return OK;
}

int dumptree(TreeElem_t* elem)
{
    assert(elem);
    if(elem->last!=NULL)
        printf("(%s",elem->data);
    if (elem->left!=NULL)dumptree(elem->left);
    if (elem->right!=NULL)dumptree(elem->right);
    if(elem->last!=NULL)
        printf(")");
}

int gotofirst(Tree* T)
{
    assert(T);
    T->current=T->first;
    return OK;
}
int gotolast(Tree* T)
{
    assert(T);
    if(T->current->last==NULL)return CANT_GO;
    T->current=T->current->last;
    return OK;
}

int gotoleft(Tree* T)
{
    assert(T);
    if(T->current->left==NULL)return CANT_GO;
    T->current=T->current->left;
    return OK;
}

int gotoright(Tree* T)
{
    assert(T);
    if(T->current->right==NULL)return CANT_GO;
    T->current=T->current->right;
    return OK;
}

int readfromfile(Tree* T,char* fname)
{
    FILE* F=fopen(fname,"r");
    assert(F);
    data_t buff;
    while(!feof(F))
    {
        buff=(data_t)calloc(1,sizeof(data_t));
        fscanf(F,"%s",buff);

        if(strcmp(buff,"(")==0)
        {

            fscanf(F,"%s",buff);

            if (T->current->left==NULL)
            {

                tree_add_left(T,buff);
            }
            else tree_add_right(T,buff);

        }
        if(strcmp(buff,")")==0)
        {
            gotolast(T);
        }

    }
    return 0;
}
int main()
{
    Tree* T;
    T=(Tree*)calloc(1,sizeof(Tree));

    tree_ctor(T,"first");

    readfromfile(T,"1.txt");

    dumptree(T->first);
    return 0;
}
