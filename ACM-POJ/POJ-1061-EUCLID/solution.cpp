// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-29 09:40
// Last modified: 2016-07-29 11:55
// Filename: solution.cpp
// Description:
#include <cstdio>

#define ll long long 

ll gcd(ll a, ll b)
{
    return b==0?a:gcd(b, a%b);
}

void extended_euclid(ll a, ll b, ll &x, ll &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return;
    }
    extended_euclid(b, a%b, x, y);
    ll t = x;
    x = y;
    y = t - a/b*y;
    return;
}


int main()
{
    ll x, y, m, n, L, a, b, c, r, p, q, t;
    while(~scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L))
    {
        b = L;
        a = n-m;
        c = x-y;
        r = gcd(a, b);
        if(c%r)
        {
            printf("Impossible\n");
            continue;
        }
        extended_euclid(a, b, p, q);
        // x = x0 + b/gcd(a,b)*t
        // y = y0 - a/gcd(a,b)*t
        // t is integer.
        
        // Calculate how many b in c*p/r at most.(c*p/r is x in ax+by=c)
        // should notice that t*b <= y
        t = c*p/r/b;  
        // Get a particular solution which x is the smallest in all solutions.
        p = c*p/r - t*b;
        if(p<0)
            p += b;
        printf("%lld\n", p);
    }
    return 0;
}
