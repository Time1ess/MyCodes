// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-22 10:04
// Last modified: 2016-07-22 10:18
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long

const ll mod=20100713;
const ll N=1e6+5;
ll factorial[N];

void solve()
{
    factorial[0] = factorial[1] = 1;
    int i;
    for(i = 2; i <= 1000000; i++)
        factorial[i] = factorial[i-1] * i % mod;
}

ll multimod(ll x, ll n, ll mod)
{
    ll tmp = x, res = 1LL;
    while(n)
    {
        if(n&1LL)
        {
            res *= tmp;
            res %= mod;
        }
        tmp *= tmp;
        tmp %= mod;
        n >>= 1LL;
    }
    return res;
}

int main()
{
    ll t, n, k, i, j;
    ll ans1, ans2, ans;
    solve();
    scanf("%lld", &t);
    while(t--)
    {
        scanf("%lld%lld", &n, &k);
        if(k==0)
        {
            printf("1\n");
            continue;
        }
        ans1 = ans2 = factorial[k];
        ans1 *= multimod(k+1, n-k, mod);
        ans1 %= mod;
        ans1 += mod;
        ans2 *= multimod(k, n-k, mod);
        ans2 %= mod;
        ans = (ans1 - ans2)%mod;
        printf("%lld\n", ans);
    }
    return 0;
}

