// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-09 09:49
// Last modified: 2016-08-09 10:07
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=510;
const int inf=1e9;

struct Edge
{
    int u, v, c;
    Edge(){}
    Edge(int u, int v, int c):u(u), v(v), c(c){}
}p[N*N];

int T, e, n, ans;
int father[N];


int cmp(const void *a, const void *b)
{
    return ((Edge *)a)->c-((Edge *)b)->c;
}


void build()
{
    for(int i=1; i <= n; i++)
        father[i] = i;
}

int find(int x)
{
    if(x != father[x])
        father[x] = find(father[x]);
    return father[x];
}

void kruskal()
{
    ans = 0;
    int cnt = 0;
    build();
    qsort(p, e, sizeof(Edge), cmp);
    for(int i=0; i < e; i++)
    {
        int fx = find(p[i].u);
        int fy = find(p[i].v);
        if(fx==fy)
            continue;
        father[fx] = fy;
        ans = p[i].c;
        cnt++;
        if(cnt==n-1)
            break;
    }
}


int main()
{
    scanf("%d", &T);
    while(T--)
    {
        e = 0;
        scanf("%d", &n);
        for(int i=1; i <= n; i++)
            for(int j=1; j <= n; j++)
            {
                scanf("%d", &p[e].c);
                p[e].u = i;
                p[e].v = j;
                e++;
            }
        kruskal();
        printf("%d\n", ans);
    }
}
