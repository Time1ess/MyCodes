// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-03 09:18
// Last modified: 2016-08-03 11:01
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

const int MAXN=1e5+2;

struct Node
{
    int cnt;
    int pos;
    Node(){}
    Node(int p, int c)
    {
        cnt = c;
        pos = p;
    }
};

Node queue[MAXN*10];
bool visited[MAXN];


int BFS(int n, int k)
{
    if(n==k)
        return 0;
    memset(visited, 0, sizeof(visited));
    int front=0, back=0;
    Node n0(n, 0);
    queue[front++] = n0;
    visited[n] = true;
    while(front!=back)
    {
        Node tmp = queue[back++];
        if(back>=MAXN)
            back = 0;
        Node n1(tmp.pos-1, tmp.cnt+1);
        Node n2(tmp.pos+1, tmp.cnt+1);
        Node n3(tmp.pos*2, tmp.cnt+1);
        if(n1.pos == k || n2.pos == k || n3.pos == k)
            return n1.cnt;
        if(n1.pos>=0&&n1.pos<=MAXN-2&&!visited[n1.pos])
        {
            queue[front++] = n1;
            if(front>=MAXN)
                front = 0;
            visited[n1.pos] = true;
        }
        if(n2.pos<=MAXN-2&&n2.pos>=0&&!visited[n2.pos])
        {
            queue[front++] = n2;
            if(front>=MAXN)
                front = 0;
            visited[n2.pos] = true;
        }
        if(n3.pos<=MAXN-2&&n3.pos>=0&&!visited[n3.pos])
        {
            queue[front++] = n3;
            if(front>=MAXN)
                front = 0;
            visited[n3.pos] = true;
        }
    }
    return -1;
}


int main()
{
    int N, K;
    while(~scanf("%d %d", &N, &K))
        printf("%d\n", BFS(N, K));
    return 0;
}
