// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-09 14:23
// Last modified: 2016-04-09 15:01
// Filename: real_solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
ll lookup[110];

int main()
{
    int T;
    scanf("%d",&T);
    for(int cc=1;cc<=T;cc++)
    {
        memset(lookup, 0, sizeof(lookup));
        int K,C,S;
        scanf("%d%d%d",&K,&C,&S);
        int s=1;
        if(2*S>K)
        {
            if(C==1)
            {
                if(K==S)
                {
                    printf("Case #%d:",cc);
                    for(int i=1;i<=K;i++)
                        printf(" %d",i);
                    printf("\n");
                }
                else
                {
                    printf("Case #%d: IMPOSSIBLE\n",cc);
                }
                continue;
            }
            for(int k=1;k<=K;k+=2)
            {
                lookup[s]=(k-1)*C+1+k;
                s++;
            }
            printf("Case #%d:",cc);
            for(int o=1;lookup[o]!=0;o++)
                printf(" %d",lookup[o]);
            printf("\n");
        }
        else
        {
            printf("Case #%d: IMPOSSIBLE\n",cc);
        }
    }
    return 0;
}
