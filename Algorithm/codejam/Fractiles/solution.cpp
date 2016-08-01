// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-09 10:40
// Last modified: 2016-04-09 10:53
// Filename: solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    int T;
    scanf("%d",&T);
    for(int cc=1;cc<=T;cc++)
    {
        int K,C,S;
        scanf("%d%d%d",&K,&C,&S);

        printf("Case #%d:",cc);
        for(int i=1;i<=S;i++)
        {
            printf(" %d",i);
        }
        printf("\n");
    }
    return 0;
}
