// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-07 14:21
// Last modified: 2016-07-07 14:45
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

struct node
{
    char name[32];
    node *lson, *rson;
    int count;
};

node *root;
int total;


void insertBST(node **root, char *name)
{
    if(*root==NULL)
    {
        node *tmp = (node *)malloc(sizeof(node));
        strcpy(tmp->name, name);
        tmp->lson = NULL;
        tmp->rson = NULL;
        tmp->count = 1;
        *root = tmp;
    }
    else
    {
        int k = strcmp(name, (*root)->name);
        if(k==0)
            (*root)->count++;
        else if(k<0)
            insertBST(&((*root)->lson), name);
        else
            insertBST(&((*root)->rson), name);
    }
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

int main()
{
    char name[32];
    total = 0;
    while(gets(name))
    {
        insertBST(&root, name);
        total++;
    }
    inorder(root);
    return 0;
}
