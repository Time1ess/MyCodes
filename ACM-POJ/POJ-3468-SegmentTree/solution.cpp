// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-04 13:01
// Last modified: 2016-07-05 10:13
// Filename: solution.cpp
// Description:
#include <cstdio>
using namespace std;

typedef long long ll;
#define N 100010

ll A[N];

struct segment
{
    ll val;
    ll add;
    int l,r,m;
}s[N<<2];


void build(int k, int l, int r)
{
    s[k].l = l;
    s[k].r = r;
    s[k].m = (l+r)>>1;
    s[k].add = 0;
    if(l==r)
    {
        s[k].val = A[l];
        return;
    }
    build(k<<1, l, s[k].m);
    build(k<<1|1, s[k].m+1, r);
    s[k].val = s[k<<1].val + s[k<<1|1].val;
}

void update(int k, int L, int R, int add)
{
    if(s[k].l==L&&s[k].r==R)
    {
        s[k].add += add;
        return;
    }
    s[k].val += (ll)add*(R-L+1);
    if(R<=s[k].m)
        update(k<<1, L, R, add);
    else
    {
        if(L>s[k].m)
            update(k<<1|1, L, R, add);
        else
        {
            update(k<<1, L, s[k].m, add);
            update(k<<1|1, s[k].m+1, R, add);
        }
    }
}

ll sum(int k, int L, int R)
{
    if(s[k].l==L&&s[k].r==R)
    {
        return s[k].val+s[k].add*(ll)(R-L+1);
    }
    if(s[k].add!=0)
    {
        s[k<<1].add += s[k].add;
        s[k<<1|1].add += s[k].add;
        s[k].val += (ll)(s[k].r-s[k].l+1)*s[k].add;
        s[k].add = 0;
    }
    if(R<=s[k].m)
        return sum(k<<1, L, R);
    else
    {
        if(L>s[k].m)
            return sum(k<<1|1, L, R);
        else
        {
            return sum(k<<1, L, s[k].m)+sum(k<<1|1, s[k].m+1, R);
        }
    }
}

int main()
{
    int n,q;
    int tmp[3];
    char c[8];
    while(scanf("%d%d", &n, &q)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%lld", &A[i]);
        }
        build(1, 1, n);
        for(int i=1;i<=q;i++)
        {
            scanf("%s", c);
            if(c[0]=='Q')
            {
                scanf("%d%d", &tmp[0], &tmp[1]);
                printf("%lld\n", sum(1, tmp[0], tmp[1]));
            }
            else if(c[0]=='C')
            {
                scanf("%d%d%d", &tmp[0], &tmp[1], &tmp[2]);
                update(1, tmp[0], tmp[1], tmp[2]);
            }
        }
    }
    return 0;
}
