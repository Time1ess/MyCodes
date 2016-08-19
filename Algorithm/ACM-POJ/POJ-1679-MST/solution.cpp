// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-19 10:42
// Last modified: 2016-08-19 11:06
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int N=110;
const int M=10010;

struct Edge
{
    int from, to, val;
    Edge(){}
    Edge(int from, int to, int val):from(from), to(to), val(val){}
};

int T;
int n, m;
int x, y, w;
int ans;
bool flag;

Edge p[M];
int f[N];

bool cmp(const Edge &e1, const Edge &e2)
{
    return e1.val < e2.val;
}

int find(int x)
{
    if(f[x] != x)
        f[x] = find(f[x]);
    return f[x];
}

int kruskal()
{
    int ans = 0;
    int fx, fy;
    flag = false;
    for(int i=0; i < n; i++)
        f[i] = i;
    sort(p, p+m, cmp);
    for(int i=0; i < m; i++)
    {
        fx = find(p[i].from);
        fy = find(p[i].to);
        if(fx == fy)
            continue;
        for(int j=i+1; j < m; j++)
        {
            if(p[j].val != p[i].val)
                break;
            if((fx == find(p[j].from)&&fy == find(p[j].to))||
                    (fx == find(p[j].to)&&fy == find(p[j].from)))
            {
                flag = true;
                break;
            }
        }
        f[fx] = fy;
        ans += p[i].val;
        if(flag)
            break;
    }
    if(flag)
        return -1;
    return ans;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &n, &m);
        for(int i=0; i < m; i++)
        {
            scanf("%d %d %d", &x, &y, &w);
            p[i].from = x;
            p[i].to = y;
            p[i].val = w;
        }
        ans = kruskal();
        if(ans < 0)
            printf("Not Unique!\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
