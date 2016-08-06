// Author: Dasrcid
// Email: youchen.du@gmail.com
// Created: 2016-08-06 09:38
// Last modified: 2016-08-06 10:25
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using std::queue;

#define ll long long
const int MAXN=1e6+10;
const int inf=1e9;

struct Edge
{
    int src, dst;
    ll weight;
    Edge(){}
    Edge(int src, int dst, ll weight):src(src), dst(dst), weight(weight){ }
}edge[MAXN];

int dis[MAXN];
bool vis[MAXN];
int head[MAXN];
int next[MAXN];
int CASE, e, p, q, src, dst;
ll weight, ans;


void add_node(int src, int dst, ll weight)
{
    edge[e].src = src;
    edge[e].dst = dst;
    edge[e].weight = weight;
    next[e] = head[src];
    head[src] = e++;
}

bool relax(int u, int v, ll c)
{
    if(dis[v] > dis[u]+c)
    {
        dis[v] = dis[u]+c;
        return true;
    }
    return false;
}

void spfa(int t)
{
    memset(vis, 0, sizeof(vis));
    for(int i=1; i <= p; i++)
        dis[i] = inf;
    dis[t] = 0;
    queue<int> que;
    vis[t] = true;
    que.push(t);
    while(!que.empty())
    {
        int pre=que.front();
        que.pop();
        vis[pre] = false;
        for(int i=head[pre]; i+1; i=next[i])
        {
            if(relax(edge[i].src, edge[i].dst, edge[i].weight)&&!vis[edge[i].dst])
            {
                que.push(edge[i].dst);
                vis[edge[i].dst] = true;
            }
        }
    }
}

void init()
{
    e = 0;
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    for(int i=0; i < q; i++)
    {
        scanf("%d %d %lld", &src, &dst, &weight);
        add_node(src, dst, weight);
    }
}

void reverse_graph()
{
    e = 0;
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    for(int i=0; i < q; i++)
        add_node(edge[i].dst, edge[i].src, edge[i].weight);
}

ll get_sum()
{
    ll res=0;
    for(int i=2; i <= p; i++)
        res += dis[i];
    return res;
}


int main()
{
    scanf("%d", &CASE);
    while(CASE--)
    {
        scanf("%d %d", &p, &q);
        init();
        spfa(1);
        ans = get_sum();
        reverse_graph();
        spfa(1);
        ans += get_sum();
        printf("%lld\n", ans);
    }
    return 0;
}
