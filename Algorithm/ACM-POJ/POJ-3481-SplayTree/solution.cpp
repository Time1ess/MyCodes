// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-12 10:13
// Last modified: 2016-07-12 11:01
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define VMIN 0
#define VMAX 1e7

struct Node
{
    int id;
    int val;
    Node *lson, *rson;
};

int maxPri, minPri;

Node *splay(int val, Node *rt)
{
    Node N, *l, *r, *y;
    if(rt == NULL)
        return NULL;
    N.lson = N.rson = NULL;
    l = r = &N;
    while(1)
    {
        if(rt->val>val)
        {
            if(rt->lson == NULL)
                break;
            if(rt->lson->val>val)
            {
                y = rt->lson;
                rt->lson = y->rson;
                y->rson = rt;
                rt = y;
                if(rt->lson == NULL)
                    break;
            }
            r->lson = rt;
            r = rt;
            rt = rt->lson;
        }
        else if(rt->val<val)
        {
            if(rt->rson == NULL)
                break;
            if(rt->rson->val<val)
            {
                y = rt->rson;
                rt->rson = y->lson;
                y->lson = rt;
                rt = y;
                if(rt->rson == NULL)
                    break;
            }
            l->rson = rt;
            l = rt;
            rt = rt->rson;
        }
        else
            break;
    }
    l->rson = rt->lson;
    r->lson = rt->rson;
    rt->lson = N.rson;
    rt->rson = N.lson;
    return rt;
}

void insert(int id, int val, Node **rt)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->id = id;
    p->val = val;
    p->lson = NULL;
    p->rson = NULL;

    if(*rt != NULL)
    {
        Node *t = splay(val, *rt);
        if(t->val>val)
        {
            p->lson = t->lson;
            p->rson = t;
            t->lson = NULL;
        }
        else
        {
            p->rson = t->rson;
            p->lson = t;
            t->rson = NULL;
        }
    }
    *rt = p;
}

void deleteNode(int val, Node **rt)
{
    Node *x;
    Node *t;
    if(*rt==NULL)
        return;
    t = splay(val, *rt);
    if(val==t->val)
    {
        if(t->lson == NULL)
            x = t->rson;
        else
        {
            x = splay(val, t->lson);
            x->rson = t->rson;
        }
        free(t);
        *rt = x;
        return;
    }
    *rt = t;
}

void print_low(Node *rt)
{
    while(rt->lson)
        rt = rt->lson;
    printf("%d\n", rt->id);
    minPri = rt->val;
}

void print_high(Node *rt)
{
    while(rt->rson)
        rt = rt->rson;
    printf("%d\n", rt->id);
    maxPri = rt->val;
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
}
