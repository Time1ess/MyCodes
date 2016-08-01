// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-18 15:06
// Last modified: 2016-07-18 17:16
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100005;

struct Tree
{
    int value;
    int dist;
    Tree *left;
    Tree *right;
};

int f[N], rk[N];
Tree *tree[N];

int Find(int x)
{
    if(x != f[x])
    {
        f[x] = Find(f[x]);
    }
    return f[x];
}

int Union(int fx, int fy)
{
    if(fx == fy)
        return fx;
    if(rk[fx] > rk[fy])
    {
        f[fy] = fx;
        if(rk[fy]+1 > rk[fx])
            rk[fx] = rk[fy]+1;
        return fx;
    }
    else
    {
        f[fx] = fy;
        if(rk[fx]+1 > rk[fy])
            rk[fy] = rk[fx]+1;
        return fy;
    }
}

int Distance(Tree *t)
{
    return t == NULL?0:t->dist;
}

void Fix(Tree *t)
{
    if(Distance(t->left)<Distance(t->right))
        swap(t->left, t->right);
    t->dist = Distance(t->right) + 1;
}

Tree* Merge(Tree *p, Tree *q)
{
    if(p == NULL)
        return q;
    if(q == NULL)
        return p;
    if(q->value>p->value)
        swap(p, q);
    p->right = Merge(p->right, q);
    Fix(p);
    return p;
}

Tree* DelMax(Tree *t)
{
    if(t != NULL)
        return Merge(t->left, t->right);
    return NULL;
}

void Init(Tree *&t, int value)
{
    t = (Tree *)malloc(sizeof(Tree));
    t->value = value;
    t->dist = 1;
    t->left = t->right = NULL;
}

int fight(int x, int y)
{
    int fx = Find(x);
    int fy = Find(y);
    if(fx==fy)
        return -1;
    Tree *t1, *t2, *t3, *t4;
    Init(t1, tree[fx]->value/2);
    t2 = DelMax(tree[fx]);
    t2 = Merge(t1, t2);
    Init(t3, tree[fy]->value/2);
    t4 = DelMax(tree[fy]);
    t4 = Merge(t3, t4);
    fy = Union(fx, fy);
    tree[fy] = Merge(t2, t4);
    return tree[fy]->value;
}

int main()
{
    int n, m, x, y;
    while(~scanf("%d", &n))
    {
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &x);
            f[i] = i;
            rk[i] = 0;
            Init(tree[i], x);
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; i++)
        {
            scanf("%d %d", &x, &y);
            printf("%d\n", fight(x, y));
        }
        for(int i = 1; i <= n; i++)
        {
            free(tree[i]);
        }
    }
    return 0;
}
