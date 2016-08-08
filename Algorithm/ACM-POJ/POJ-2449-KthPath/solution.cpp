// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-08 09:33
// Last modified: 2016-08-08 12:36
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <queue>

using std::priority_queue;



const int N=1010;
const int M=100010;
const int inf=1e9;

int dis[N];
int vis[N];
int n, m, s, t, k, e;
int next[M], next1[M];
int head[N], head1[N];

struct Node
{
    int u, v, c;
    Node(){}
    Node(int v):v(v){}
    Node(int v, int c):v(v), c(c){}
    Node(int u, int v, int c):u(u), v(v), c(c){}
    bool operator< (const Node &p) const
    {
        return c+dis[v]>p.c+dis[p.v];
    }
}nodes[M];


void add_node(int u, int v, int c)
{
    nodes[e].u = u;
    nodes[e].v = v;
    nodes[e].c = c;
    next[e] = head[u];
    head[u] = e;
    next1[e] = head1[v];
    head1[v] = e++;
}

void dij()
{
    memset(vis, 0, sizeof(vis));
    for(int i=1; i <= n; i++)
        dis[i] = inf;
    dis[t] = 0;
    priority_queue<Node> que;
    que.push(Node(t));
    while(!que.empty())
    {
        Node pre=que.top();
        que.pop();
        vis[pre.v] = true;
        for(int i=head1[pre.v];i+1;i=next1[i])
        {
            if(dis[nodes[i].u]>dis[pre.v]+nodes[i].c)
            {
                dis[nodes[i].u] = dis[pre.v]+nodes[i].c;
                que.push(Node(nodes[i].u));
            }
        }
        while(!que.empty()&&vis[que.top().v])
            que.pop();
    }
}

int a_star()
{
    priority_queue<Node> que;
    que.push(Node(s, 0));
    while(!que.empty())
    {
        Node pre=que.top();
        que.pop();
        if(pre.v==t&&--k==0)
                return pre.c;
        for(int i=head[pre.v]; i+1; i=next[i])
            que.push(Node(nodes[i].v, pre.c+nodes[i].c));
    }
    return -1;
}

int main()
{
    while(~scanf("%d %d", &n, &m))
    {
        e = 0;
        memset(head, -1, sizeof(head));
        memset(head1, -1, sizeof(head1));
        for(int i=1; i <= m; i++)
        {
            scanf("%d %d %d", &s, &t, &k);
            add_node(s, t, k);
        }
        scanf("%d %d %d", &s, &t, &k);
        dij();
        if(dis[s]==inf)
        {
            printf("-1\n");
            continue;
        }
        if(s==t)
            k++;
        printf("%d\n", a_star());
    }
    return 0;
}
