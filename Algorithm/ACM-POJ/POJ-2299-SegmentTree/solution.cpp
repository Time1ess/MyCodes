// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-02 14:47
// Last modified: 2016-07-04 09:53
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAXN 500010
#define ll long long

ll a[MAXN];
int s[MAXN<<2];

struct node
{
    int idx;
    ll val;
}tmp[MAXN];

bool cmp(const node &p, const node &q)
{
    return p.val<q.val;
}

void editTree(int k, int l, int r, int num, int val)
{
    s[k]+=val;
    if(l==r)
        return;
    int mid = (l+r)>>1;
    if(num<=mid)
        editTree(2*k, l, mid, num, val);
    else
        editTree(2*k+1, mid+1, r, num, val);
} 

int search(int k, int l, int r, int L, int R)
{
    if(L<=l&&R>=r)
        return s[k];
    int mid = (l+r)>>1;
    int ans = 0;
    if(L<=mid)
        ans += search(2*k, l, mid, L, R);
    if(R>mid)
        ans += search(2*k+1, mid+1, r, L, R);
    return ans;
}

int main()
{
    int n;
    while(scanf("%d", &n)&&n!=0)
    {
        memset(tmp, 0, sizeof(tmp));
        memset(a, 0, sizeof(a));
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            editTree(1, 1, n, i, 1);
            tmp[i].idx=i;
            tmp[i].val=a[i];
        }
        sort(tmp+1, tmp+n+1, cmp);
        ll ans = 0;
        for(int i=1;i<=n;i++)
        {
            ans += (search(1, 1, n, 1, tmp[i].idx)-1);
            editTree(1, 1, n, tmp[i].idx, -1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
