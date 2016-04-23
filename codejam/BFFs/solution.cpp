// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-16 09:42
// Last modified: 2016-04-16 10:03
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define SIZE 1010

int BFFs[SIZE];

int main()
{
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        int ans=0;
        memset(relations, 0, sizeof(relations));
        int N;
        scanf("%d", &N);
        int bff;
        for(int k=1;k<=N;k++)
        {
            scnaf("%d", &bff);
            BFFs[k]=bff;
        }
        printf("Case #%d: %d", i, ans);
    }
    return 0;
