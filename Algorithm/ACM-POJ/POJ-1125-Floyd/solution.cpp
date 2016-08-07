// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-07 10:19
// Last modified: 2016-08-07 10:28
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=110;
const int inf=1e9;

int dis[N][N];
int num, u, v, d, p;

int main()
{
    while(~scanf("%d", &num)&&num)
    {
        for(int i=0; i < N; i++)
        {
            for(int j=0; j < N; j++)
                dis[i][j] = inf;
            dis[i][i] = 0;
        }
        for(int i=1; i <= num; i++)
        {
            scanf("%d", &p);
            for(int j=0; j < p; j++)
            {
                scanf("%d %d", &v, &d);
                dis[i][v] = d;
            }
        }
        for(int k=1; k <= num; k++)
            for(int i=1; i <= num; i++)
                for(int j=1; j <= num; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);

        int root=0, tmp=inf;
        for(int i=1; i <= num; i++)
        {
            int maximum = 0;
            for(int j=1; j <= num; j++)
                if(dis[i][j] > maximum)
                    maximum = dis[i][j];
            if(tmp > maximum)
            {
                tmp = maximum;
                root = i;
            }
        }
        if(root)
            printf("%d %d\n", root, tmp);
        else
            printf("disjoint\n");
    }
    return 0;
}
