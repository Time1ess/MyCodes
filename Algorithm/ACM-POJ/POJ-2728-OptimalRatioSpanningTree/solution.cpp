// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-20 09:50
// Last modified: 2016-08-20 10:59
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cmath>

using namespace std;

const int MAXN=1010;
const int inf=1e9;

struct Point
{
    double x, y, z;
    Point(){}
    Point(double x, double y, double z):x(x), y(y), z(z){}
}p[MAXN];

int n;
double graph[MAXN][MAXN];
double dis[MAXN];
bool vis[MAXN];

double _dis(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void reset_graph()
{
    for(int i=1; i <= n; i++)
        for(int j=1; j <= n; j++)
                graph[i][j] = i==j? 0: inf;
}

void gen_graph(double l)
{
    reset_graph();
    for(int i=1; i <= n; i++)
        for(int j=i+1; j <= n; j++)
            graph[i][j] = graph[j][i] = -l*_dis(p[i], p[j])+fabs(p[i].z-p[j].z); // cost/length
}

double prim()
{
    double ans=0;
    double tmp;
    for(int i=1; i <= n ; i++)
    {
        vis[i] = false;
        dis[i] = graph[1][i];
    }
    vis[1] = true;
    for(int i=1; i < n; i++)
    {
        tmp=inf;
        int k;
        for(int j=1; j <= n; j++)
            if(!vis[j]&&tmp>dis[j])
            {
                tmp = dis[j];
                k = j;
            }
        vis[k] = true;
        ans += dis[k];
        for(int j=1; j <= n; j++)
            if(!vis[j]&&dis[j]>graph[j][k])
                dis[j] = graph[j][k];
    }
    return ans;
}


int main()
{
    double l, r, mid;
    while(~scanf("%d", &n)&&n)
    {
        for(int i=1; i <= n; i++)
            scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
        l = 0;
        r = 100;
        while(r-l > 0.0001)
        {
            mid = (l+r)/2;
            gen_graph(mid);
            if(prim()>0)
                l = mid;
            else
                r = mid;
        }
        printf("%.3lf\n", l);
    }
    return 0;
}
