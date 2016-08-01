// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-04 10:02
// Last modified: 2016-07-04 10:11
// Filename: solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 500010
#define ll long long

ll a[MAXN];
int idxs[MAXN];
ll c[MAXN];


bool cmp(const int p, const int q)
{
    return a[p]<a[q];
}

int lowbit(int n)
{
    return n&(-n);
}

int sum(int end)
{
    int sum = 0;
    while(end>0)
    {
        sum += c[end];
        end -= lowbit(end);
    }
    return sum;
}

void update(int pos, int num,int n)
{
    while(pos<=n)
    {
        c[pos] += num;
        pos += lowbit(pos);
    }
}


int main()
{
    int n;
    while(scanf("%d", &n)&&n!=0)
    {
        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(c));
        memset(idxs, 0, sizeof(idxs));
        for(int i=1;i<=n;i++)
        {
            scanf("%lld", &a[i]);
            idxs[i] = i;
            update(i, 1, n);
        }
        sort(idxs+1, idxs+1+n, cmp);
        ll ans = 0;
        for(int i=1;i<=n;i++)
        {
            ans += sum(idxs[i]-1);
            update(idxs[i], -1, n);
        }
        printf("%lld\n", ans);
    }
    return 0;
}

