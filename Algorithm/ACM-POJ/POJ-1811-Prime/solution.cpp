// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-01 10:08
// Last modified: 2016-08-01 11:10
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>


#define ll long long

int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

ll gcd(ll a, ll b)
{
    ll c;
    while(b)
    {
        c=a%b;
        a=b;
        b=c;
    }
    return a;
}

ll multi(ll a, ll b, ll n)
{
    ll tmp=0;
    while(b)
    {
        if(b&1)
        {
            tmp += a;
            if(tmp >= n)
                tmp -= n;
        }
        a <<= 1;
        if(a >= n)
            a -= n;
        b >>= 1;
    }
    return tmp;
}


ll multimod(ll a, ll b, ll n)
{
    ll res=1;
    while(b)
    {
        if(b&1)
            res = multi(res, a, n);
        a = multi(a, a, n);
        b >>= 1;
    }
    return res;
}


bool Miller_Rabin(ll n)
{
    if(n==2)
        return true;
    if(n<2||!(n&1))
        return false;
    ll k=0, i, j, m, a;
    m = n-1;
    while(!(m&1))
    {
        m >>= 1;
        k++;
    }
    for(i=0; i < 10; i++)
    {
        if(primes[i]>=n)
            return true;
        a = multimod(primes[i], m, n);  //a^(n-1)≡1(mod(n))
        if(a==1)
            continue;
        for(j=0; j < k; j++)
        {
            if(a == n-1)
                break;
            a = multi(a, a, n);
        }
        if(j == k)
            return false;
    }
    return true;
}

ll pollard_rho(ll c, ll n)
{
    ll i, x, y, k ,d;
    i = 1;
    x = y = rand() % n;
    k = 2;
    do
    {
        i++;
        d = gcd(n+y-x, n);
        if(d > 1 && d < n)
            return d;
        if(i == k)
        {
            y = x;
            k <<= 1;
        }
        x = (multi(x, x, n)+n-c) % n;
    }while(y != x);
    return n;
}

ll rho(ll n)
{
    if(Miller_Rabin(n))
        return n;
    ll t=n;
    while(t>=n)
        t = pollard_rho(rand()%(n-1)+1, n);
    ll a = rho(t);
    ll b = rho(n/t);
    return a<b?a:b;
}


int main()
{
    ll n;
    int CASE;
    scanf("%d", &CASE);
    while(CASE--)
    {
        scanf("%lld", &n);
        if(Miller_Rabin(n))
            printf("Prime\n");
        else
            printf("%lld\n", rho(n));
    }
    return 0;
}
