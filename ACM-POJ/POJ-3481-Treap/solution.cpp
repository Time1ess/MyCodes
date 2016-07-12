// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-12 14:27
// Last modified: 2016-07-12 14:57
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Node
{
    int id, val;
    Node *lson, *rson;
};

int minPri, maxPri;

void RRotate(Node **t)
{
    Node *p = (*t)->lson;
    (*t)->lson = p->rson;
    p->rson = *t;
    *t = p;
}

void LRotate(Node **t)
{
    Node *p = (*t)->rson;
    (*t)->rson = p->lson;
    p->lson = *t;
    *t = p;
}

void insert(int id, int val, Node **t)
{
    if(*t == NULL)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->id = id;
        p->val = val;
        p->lson = p->rson = NULL;
        *t = p;
    }
    else if((*t)->val>val)
    {
        insert(id, val, &((*t)->lson));
        if((*t)->lson->val<(*t)->val)
            RRotate(t);
    }
    else
    {
        insert(id, val, &((*t)->rson));
        if((*t)->rson->val<(*t)->val)
            LRotate(t);
    }
}

void deleteNode(int val, Node **t)
{
    if(val == (*t)->val)
    {
        if(!(*t)->lson||!(*t)->rson)
        {
            Node *tmp = (*t);
            if(!(*t)->lson)
                *t = (*t)->rson;
            else
                *t = (*t)->lson;
            free(tmp);
        }
        else
        {
            if((*t)->lson->val<(*t)->rson->val)
            {
                RRotate(t);
                deleteNode(val, &((*t)->rson));
            }
            else
            {
                LRotate(t);
                deleteNode(val, &((*t)->lson));
            }
        }
    }
    else if(val<(*t)->val)
        deleteNode(val, &((*t)->lson));
    else
        deleteNode(val, &((*t)->rson));
}

void print_low(Node *t)
{
    while(t->lson)
        t = t->lson;
    printf("%d\n", t->id);
    minPri = t->val;
}

void print_high(Node *t)
{
    while(t->rson)
        t = t->rson;
    printf("%d\n", t->id);
    maxPri = t->val;
}

int main()
{
    int type, id, val;
    Node *root = NULL;

    while(~scanf("%d", &type)&&type!=0)
    {
        if(type == 1)
        {
            scanf("%d%d", &id, &val);
            insert(id, val, &root);
        }
        else if(type == 2)
        {
            if(root == NULL)
            {
                printf("0\n");
                continue;
            }
            print_high(root);
            deleteNode(maxPri, &root);
        }
        else
        {
            if(root == NULL)
            {
                printf("0\n");
                continue;
            }
            print_low(root);
            deleteNode(minPri, &root);
        }
    }
    return 0;
}
