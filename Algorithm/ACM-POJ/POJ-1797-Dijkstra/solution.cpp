// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-05 09:22
// Last modified: 2016-08-05 10:04
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;

int a[N][N];
bool visited[N];
int dis[N];
int CASE, n, m, s, e, weight;

void dij(int src)
{
    memset(visited, 0, sizeof(visited));
    memset(dis, 0, sizeof(dis));
    for(int i=1; i <= n; i++)
        dis[i] = a[src][i];
    visited[src] = true;
    for(int i=1; i <= n; i++)
    {
        int tmp = 0, k;
        for(int j=1; j <= n; j++)
        {
            if(visited[j])
                continue;
            if(tmp <= dis[j])
            {
                tmp = dis[j];
                k = j;
            }
        }
        visited[k] = true;
        for(int j=1; j <= n; j++)
        {
            if(visited[j])
                continue;
            dis[j] = max(dis[j], min(dis[k], a[k][j]));
        }
    }
}


int main()
{
    scanf("%d", &CASE);
    for(int i=1; i <= CASE; i++)
    {
        scanf("%d %d", &n, &m);
        memset(a, 0, sizeof(a));
        for(int j=0; j < m; j++)
        {
            scanf("%d %d %d", &s, &e, &weight);
            a[s][e] = a[e][s] = weight; // IMPORTANT: consider weightes of s->t and t->s are the same.
        }
        dij(1);
        printf("Scenario #%d:\n%d\n\n", i, dis[n]);
    }
}
