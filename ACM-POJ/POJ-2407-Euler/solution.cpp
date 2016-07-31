// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-31 10:00
// Last modified: 2016-07-31 10:16
// Filename: solution.cpp
// Description:
#include <cstdio>


int main()
{
    int n, ans, tmp;
    while(scanf("%d", &n)&&n!=0)
    {
        ans = n;
        tmp = n;
        for(int i=2; i*i<=n;i++)
        {
            if(n%i==0)
            {
                ans = ans/i*(i-1);
                while(n%i==0)
                    n/=i;
            }
        }
        if(n!=1)
            ans = ans/n*(n-1);
        printf("%d\n", tmp==1?0:ans);
    }
    return 0;
}
