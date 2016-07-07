// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-06 14:27
// Last modified: 2016-07-07 10:30
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100010
#define CN 40

struct segment
{
    int l, r, color, cover;
}s[N<<2];

int colors[CN];
int n, T, O;

void build(int k, int l, int r)
{
    s[k].l = l;
    s[k].r = r;
    s[k].color = 1;
    s[k].cover = 1;
    if(l==r)
        return;
    int mid = (l+r)>>1;
    build(k*2, l, mid);
    build(k*2+1, mid+1, r);
}

void update(int k, int l, int r, int color)
{
    if(s[k].l==l&&s[k].r==r)
    {
        s[k].color = color;
        s[k].cover = 1;
        return;
    }
    if(s[k].cover==1)
    {
        s[k<<1].color = s[k].color;
        s[k<<1].cover = 1;
        s[k<<1|1].color = s[k].color;
        s[k<<1|1].cover = 1;
        s[k].cover = 0;
    }
    int mid = (s[k].l+s[k].r)>>1;
    if(r<=mid)
        update(k<<1, l, r, color);
    else if(l>mid)
        update(k<<1|1, l, r, color);
    else
    {
        update(k<<1, l, mid, color);
        update(k<<1|1, mid+1, r, color);
    }
}

void query(int k, int l, int r)
{
    if(s[k].cover==1||(s[k].l==l&&s[k].r==r&&l==r))
    {
        colors[s[k].color]++;
        return;
    }
    int mid = (s[k].l+s[k].r)>>1;
    if(r<=mid)
        query(k<<1, l, r);
    else if(l>mid)
        query(k<<1|1, l, r);
    else
    {
        query(k<<1, l, mid);
        query(k<<1|1, mid+1, r);
    }
}

int getColors(int k, int l, int r)
{
    memset(colors, 0, sizeof(colors));
    query(k, l, r);
    int ans = 0;
    for(int i=1;i<=T;i++)
        if(colors[i]!=0)
            ans++;
    return ans;
}

void swap(int &x, int &y)
{
    int tmp;
    if(x>y)
    {
        tmp = y;
        y = x;
        x = tmp;
    }
}

int main()
{
    char ops[3];
    int a, b, c;
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d %d", &T, &O);
    while(O--)
    {
        scanf("%s", ops);
        if(ops[0]=='C')
        {
            scanf("%d %d %d", &a, &b, &c);
            swap(a, b);
            update(1, a, b, c);
        }
        else
        {
            scanf("%d %d", &a, &b);
            swap(a, b);
            printf("%d\n", getColors(1, a, b));
        }
    }
    return 0;
}
