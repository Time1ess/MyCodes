// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-31 11:10
// Last modified: 2016-07-31 11:16
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>



bool not_prime[1000000];


void init()
{
    int i, j;
    memset(not_prime, 0, sizeof(not_prime));
    not_prime[0] = not_prime[1] = 1;
    for(i=2;i<1001;i++)
    {
        if(!not_prime[i])
        {
            for(j=i*i;j<1000000;j+=i)
                not_prime[j] = 1;
        }
    }
}

int main()
{
    int n, i, flag;
    init();
    while(scanf("%d", &n)&&n)
    {
        flag = 0;
        for(i=2;i<=n/2;i++)
        {
            if(!not_prime[i]&&!not_prime[n-i])
            {
                printf("%d = %d + %d\n", n, i, n-i);
                flag = 1;
                break;
            }
        }
        if(flag==0)
            printf("Goldbach's conjecture is wrong.\n");
    }
    return 0;
}
