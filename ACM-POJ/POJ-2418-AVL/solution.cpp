// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-08 14:51
// Last modified: 2016-07-08 16:01
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct node
{
    char name[32];
    node *lson, *rson;
    int height;
    int count;
};

node *root;
int total;

void LLRotate(node **rt);
void LRRotate(node **rt);
void RLRotate(node **rt);
void RRRotate(node **rt);


int Max(int a, int b)
{
    return a>b?a:b;
}

int height(node *p)
{
    if(p==NULL)
        return -1;
    else
        return p->height;
}

void LLRotate(node **rt)
{
    node *tmp = (*rt)->lson;
    (*rt)->lson = tmp->rson;
    tmp->rson = *rt;

    (*rt)->height = Max(height((*rt)->lson), height((*rt)->rson))+1;
    tmp->height = Max(height(tmp->lson), (*rt)->height)+1;

    *rt = tmp;
}

void RRRotate(node **rt)
{
    node *tmp = (*rt)->rson;
    (*rt)->rson = tmp->lson;
    tmp->lson = *rt;

    (*rt)->height = Max(height((*rt)->lson), height((*rt)->rson))+1;
    tmp->height = Max(height(tmp->lson), (*rt)->height)+1;

    *rt = tmp;
}

void LRRotate(node **rt)
{
    RRRotate(&((*rt)->lson));
    LLRotate(rt);
}

void RLRotate(node **rt)
{
    LLRotate(&((*rt)->rson));
    RRRotate(rt);
}

void inorder(node *root)
{
    if(root!=NULL)
    {
        inorder(root->lson);
        printf("%s %.4f\n", root->name, (double)(root->count)/total*100);
        inorder(root->rson);
    }
}

void insertAVL(node **rt, char *nm)
{
    if(*rt == NULL)
    {
        node *p = (node *)malloc(sizeof(node));
        strcpy(p->name, nm);
        p->height = 0;
        p->lson = NULL;
        p->rson = NULL;
        p->count = 1;
        *rt = p;
    }
    else if(strcmp(nm, (*rt)->name)<0)
    {
        insertAVL(&((*rt)->lson), nm);
        if(height((*rt)->lson)-height((*rt)->rson)==2)
        {
            if(strcmp(nm, (*rt)->lson->name)<0)
                LLRotate(rt);
            else
                LRRotate(rt);
        }
    }
    else if(strcmp(nm, (*rt)->name)>0)
    {
        insertAVL(&((*rt)->rson), nm);
        if(height((*rt)->rson)-height((*rt)->lson)==2)
        {
            if(strcmp(nm, (*rt)->rson->name)<0)
                RLRotate(rt);
            else
                RRRotate(rt);
        }
    }
    else
        (*rt)->count++;
    (*rt)->height =  Max(height((*rt)->lson), height((*rt)->rson))+1;
}


int main()
{
    char name[32];
    total = 0;
    while(gets(name))
    {
        insertAVL(&root, name);
        total++;
    }
    inorder(root);
    return 0;
}
