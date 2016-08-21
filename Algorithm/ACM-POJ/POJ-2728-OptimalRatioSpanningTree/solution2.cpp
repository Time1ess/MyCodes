// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-21 10:50
// Last modified: 2016-08-21 11:11
// Filename: solution2.cpp
// Description:
#include <cstdio>
#include <cmath>

#define max(a,b) (a)>(b)?(a):(b)

const int MAXN=1010;
const int inf=1e9;
const double eps=1e-6;

double g[MAXN][MAXN], d[MAXN][MAXN], h[MAXN][MAXN];
bool vis[MAXN];
double dis[MAXN];
double ht, dt, tc;
double L;
int pri[MAXN];
int N;


void prim(double ratio)
{
    ht = dt = tc = 0;
    double mmin;
    int k;
    for(int i=1; i <= N; i++)
    {
        vis[i] = 1;
        for(int j=1; j <= N; j++)
            g[i][j] = g[j][i] = h[i][j] - ratio*d[i][j];
        dis[i] = inf;
    }
    dis[1] = 0.0;
    pri[1] = 1;
    for(int i=1; i <= N; i++)
    {
        mmin = inf;
        k = -1;
        for(int j=1; j <= N; j++)
        {
            if(vis[j]&&mmin>dis[j])
            {
                k = j;
                mmin = dis[j];
            }
        }
        vis[k] = 0;
        dt += d[k][pri[k]];
        ht += h[k][pri[k]];
        tc += dis[k];
        for(int j=1; j <= N; j++)
        {
            if(vis[j]&&dis[j]>g[k][j])
            {
                dis[j] = g[k][j];
                pri[j] = k;
            }
        }
    }
}


int main()
{
    double x[MAXN], y[MAXN], z[MAXN];
    double maxx;
    while(~scanf("%d", &N)&&N)
    {
        maxx = 0;
        for(int i=1; i <= N; i++)
            scanf("%lf %lf %lf", &x[i], &y[i], &z[i]);
        for(int i=1; i <= N; i++)
            for(int j=1; j <= N; j++)
            {
                d[j][i] = d[i][j] = i == j? 0: sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                h[j][i] = h[i][j] = i == j? 0: fabs(z[i]-z[j]);
                maxx = max(maxx, h[i][j]);
            }
        L = N*maxx; 
        while(prim(L),fabs(tc)>eps)
            L = ht/dt;
        printf("%.3lf\n", L);
    }
    return 0;
}
