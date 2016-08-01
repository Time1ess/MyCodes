// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-09 07:05
// Last modified: 2016-04-10 11:00
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;


int mymap[10];
int MAX=100000;

void update_map(int val)
{
    while(val)
    {
        mymap[val%10]=1;
        val/=10;
    }
}
int end_map()
{
    for(int i=0;i<10;i++)
        if(!mymap[i])
            return 0;
    return 1;
}

int main()
{
    int CASE;
    scanf("%d",&CASE);
    for(int cc=1;cc<=CASE;cc++)
    {
        memset(mymap,0,sizeof(mymap));
        int N;
        scanf("%d",&N);
        int round;
        int end=0;
        if(N==0)
        {
            printf("Case #%d: INSOMNIA\n",cc);
            continue;
        }
        for(round=1;round<=1000;round++)
        {
            update_map(round*N);
            if(end_map())
            {
                printf("Case #%d: %d\n",cc,round*N);
                end=1;
            }
            if(end)
                break;
        }
        if(round==1000)
            printf("Case #%d: INSOMNIA\n",cc);
    }
    return 0;
}
