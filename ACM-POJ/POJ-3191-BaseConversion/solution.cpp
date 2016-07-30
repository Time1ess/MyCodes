// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-30 11:02
// Last modified: 2016-07-30 11:13
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

#define ll long long

template<class T>
void swap(T &p, T &q)
{
    T t = p;
    p = q;
    q = t;
}


int main()
{
    ll a;
    int ans[100];
    int i, c;
    while(~scanf("%lld", &a))
    {
       if(a==0)
       {
           printf("0\n");
           continue;
       }
       i = c = 0;
       memset(ans, 0, sizeof(ans));
       while(a)
       {
           ans[i] = a%2;
           if(a<0)
               ans[i] = -ans[i];
           a -= ans[i];
           a /= -2;
           i++;
       }
       c = i;
       for(i=0;i<c/2;i++)
           swap(ans[i], ans[c-i-1]);
       for(i=0;i<c;i++)
           printf("%d", ans[i]);
       printf("\n");
    }
    return 0;
}
