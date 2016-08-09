// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-09 09:35
// Last modified: 2016-08-09 09:48
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

const int N=110;
const int inf=1e9;

int a[N][N];
bool vis[N];
int dis[N];

int n, ans;


void prim()
{
    memset(vis, 0, sizeof(vis));
    for(int i=1; i <= n; i++)
        dis[i] = inf;
    ans = 0;
    dis[1] = 0;
    for(int i=1; i <= n; i++)
    {
        int tmp=inf, k=1;
        for(int j=1; j <= n; j++)
            if(!vis[j]&&dis[j] < tmp)
            {
                tmp = dis[j];
                k = j;
            }
        if(tmp == inf)
            return;
        vis[k] = true;
        ans += tmp;
        for(int j=1; j <= n; j++)
        {
            if(!vis[j]&&dis[j]>a[k][j])
                dis[j] = a[k][j];
        }
    }
}

int main()
{
    while(~scanf("%d", &n)&&n)
    {
        for(int i=1; i <= n; i++)
            for(int j=1; j <= n; j++)
                scanf("%d", &a[i][j]);
        prim();
        printf("%d\n", ans);
    }
}
