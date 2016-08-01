// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-05 10:13
// Last modified: 2016-07-05 10:13
// Filename: solution.cpp
// Description:
#include <cstdio>
using namespace std;

#define ll long long
#define N 100000+10

ll sum[N];
ll add[N], i_add[N];

ll lowbit(ll n)
{
    return n&(-n);
}

ll query(int end, ll *c)
{
    ll ans = 0;
    while(end>0)
    {
        ans += c[end];
        end -= lowbit(end);
    }
    return ans;
}

void update(int pos, int num, int n, ll *c)
{
    while(pos<=n)
    {
        c[pos] += num;
        pos += lowbit(pos);
    }
}


int main()
{
    int n, q;
    int x, y, v;
    char c[8];
    while(scanf("%d%d", &n, &q)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%lld", &sum[i]);
            sum[i] += sum[i-1];
        }
        for(int i=1;i<=q;i++)
        {
            scanf("%s", c);
            if(c[0]=='Q')
            {
                scanf("%d%d", &x, &y);
                printf("%lld\n", sum[y]-sum[x-1]+(y+1)*query(y, add)-x*query(x-1, add)-query(y, i_add)+query(x-1, i_add));
            }
            else if(c[0]=='C')
            {
                scanf("%d%d%d", &x, &y, &v);
                update(x, v, n, add);
                update(y+1, -v, n, add);
                update(x, x*v, n, i_add);
                update(y+1, -(y+1)*v, n, i_add);
            }
        }
    }
    return 0;
}
