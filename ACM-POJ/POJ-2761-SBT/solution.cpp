// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-13 12:30
// Last modified: 2016-07-13 14:56
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 100010
#define M 50010


struct Query
{
    int l,r,k;
    int index;
};

Query q[M];
int key[N], left[N], right[N], size[N];
int arr[N], ans[N];
int cnt;

void RRotate(int &t)
{
    int p = left[t];
    left[t] = right[p];
    right[p] = t;
    size[p] = size[t];
    size[t] = size[left[t]]+size[right[t]]+1;
    t = p;
}

void LRotate(int &t)
{
    int p = right[t];
    right[t] = left[p];
    left[p] = t;
    size[p] = size[t];
    size[t] = size[left[t]]+size[right[t]]+1;
    t = p;
}

void Maintain(int &t)
{
    if(size[left[left[t]]]>size[right[t]])
    {
        RRotate(t);
        Maintain(right[t]);
        Maintain(t);
    }
    else if(size[right[left[t]]]>size[right[t]])
    {
        LRotate(left[t]);
        RRotate(t);
        Maintain(right[t]);
        Maintain(left[t]);
        Maintain(t);
    }
    else if(size[right[right[t]]]>size[left[t]])
    {
        LRotate(t);
        Maintain(left[t]);
        Maintain(t);
    }
    else if(size[left[right[t]]]>size[left[t]])
    {
        RRotate(right[t]);
        LRotate(t);
        Maintain(right[t]);
        Maintain(left[t]);
        Maintain(t);
    }
}

void Insert(int &t, int val)
{
    if(t == 0)
    {
        key[t = ++cnt] = val;
        size[t] = 1;
    }
    else
    {
        size[t]++;
        if(val<key[t])
            Insert(left[t], val);
        else
            Insert(right[t], val);
        Maintain(t);
    }
}

int Delete(int &t, int val)
{
    size[t]--;
    if(val==key[t]||(val<key[t]&&left[t]==0)||val>key[t]&&right[t]==0)
    {
        int r = key[t];
        if(left[t]==0||right[t]==0)
            t = left[t]+right[t];
        else
            key[t] = Delete(left[t], val+1);
        return r;
    }
    else
    {
        if(val<key[t])
            return Delete(left[t], val);
        else
            return Delete(right[t], val);
    }
}

int Select(int t, int k)
{
    int r = size[left[t]] + 1;
    if(k == r)
        return key[t];
    else if(k < r)
        return Select(left[t], k);
    else
        return Select(right[t], k-r);
}

int cmp(const void *a, const void *b)
{
    Query *qa=(Query *)a, *qb=(Query *)b;
    if(qa->l!=qb->l)
        return qa->l-qb->l;
    else
        return qa->r-qb->r;
}

int main()
{
    int n, m;
    int T;
    int lastl, lastr;
    lastl = 1;
    lastr = 0;
    T = cnt = 0;
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1;i<=n;i++)
            scanf("%d", &arr[i]);
        for(int i=1;i<=m;i++)
        {
            scanf("%d %d %d", &q[i].l, &q[i].r, &q[i].k);
            q[i].index = i;
        }
        qsort(q+1, m, sizeof(Query), cmp);

        for(int i=1;i<=m;i++)
        {
            int l = q[i].l, r = q[i].r, k = q[i].k;
            if(lastr < l)
            {
                for(int j=lastl;j<=lastr;j++)
                    Delete(T, arr[j]);
                for(int j=l;j<=r;j++)
                    Insert(T, arr[j]);
            }
            else if(lastr <= r)
            {
                for(int j=lastl;j<l;j++)
                    Delete(T, arr[j]);
                for(int j=lastr+1;j<=r;j++)
                    Insert(T, arr[j]);
            }
            else
            {
                for(int j=lastl;j<l;j++)
                    Delete(T, arr[j]);
                for(int j=r+1;j<=lastr;j++)
                    Insert(T, arr[j]);
            }
            lastl = l;
            lastr = r;
            ans[q[i].index] = Select(T, k);
        }
        for(int i=1;i<=m;i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
