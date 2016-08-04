// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-04 09:29
// Last modified: 2016-08-04 10:28
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

const int N=362890;

int H(const char s[]);

struct Node
{
    char s[10];
    int g;
    int h;
    Node(char s[], int g):g(g)
    {
        strcpy(this->s, s);
        this->h = H(s);
    }
    bool operator <(const Node &q) const
    {
        return g+h > q.g+q.h;
    }
};

int fac[]={1,1,2,6,24,120,720,5040,40320,362880};
int visited[N], ans[N];
priority_queue<Node> que;

int contour(char s[])
{
    bool has[10]={0};
    int res=0;
    for(int i=0;i<9;i++)
    {
        int x = s[i]-'0';
        int cnt=0;
        for(int j=1; j < x; j++)
            if(!has[j])
                cnt++;
        res += cnt*fac[8-i];
        has[x] = true;
    }
    return res;
}

int H(const char s[])
{
    int res = 0;
    for(int i=0; i<9; i++)
        res += abs(s[i]-(i+'1'));
    return res;
}

int main()
{
    char puzzle[10], str[10];
    int c, trace, x;
    while(~scanf("%s", str))
    {
        puzzle[0] = str[0]=='x'?'9':str[0];
        for(int i=1; i<9; i++)
        {
            scanf("%s", str);
            puzzle[i] = str[0]=='x'?'9':str[0];
        }
        puzzle[9] = '\0';
        memset(visited, 0, sizeof(visited));
        while(!que.empty())
            que.pop();
        visited[contour(puzzle)] = 100;
        que.push(Node(puzzle, 0));
        while(!que.empty())
        {
            Node pre = que.top();
            que.pop();
            x = 0;
            while(pre.s[x] != '9') x++;
            if(x % 3)  // left
            {
                strcpy(str, pre.s);
                str[x] = str[x-1];
                str[x-1] = '9';
                c = contour(str);
                if(!visited[c])
                {
                    visited[c] = -1;
                    que.push(Node(str, pre.g+1));
                }
            }
            if(x >= 3)  // top
            {
                strcpy(str, pre.s);
                str[x] = str[x-3];
                str[x-3] = '9';
                c = contour(str);
                if(!visited[c])
                {
                    visited[c] = -3;
                    que.push(Node(str, pre.g+1));
                }
            }
            if(x < 6)  // bottom
            {
                strcpy(str, pre.s);
                str[x] = str[x+3];
                str[x+3] = '9';
                c = contour(str);
                if(!visited[c])
                {
                    visited[c] = 3;
                    que.push(Node(str, pre.g+1));
                }
            }
            if(x % 3 != 2)  // right
            {
                strcpy(str, pre.s);
                str[x] = str[x+1];
                str[x+1] = '9';
                c = contour(str);
                if(!visited[c])
                {
                    visited[c] = 1;
                    que.push(Node(str, pre.g+1));
                }
            }
            if(visited[0])  // contour for "123456789"
                break;
        }
        trace = 0;
        c = 0;
        strcpy(str, "123456789");
        while(visited[trace]!=100)
        {
            x = 0;
            while(str[x] != '9') x++;
            switch(visited[trace])
            {
                case 1:
                    str[x] = str[x-1];
                    str[x-1] = '9';
                    ans[c++] = 'r';
                    break;
                case -1:
                    str[x] = str[x+1];
                    str[x+1] = '9';
                    ans[c++] = 'l';
                    break;
                case 3:
                    str[x] = str[x-3];
                    str[x-3] = '9';
                    ans[c++] = 'd';
                    break;
                case -3:
                    str[x] = str[x+3];
                    str[x+3] = '9';
                    ans[c++] = 'u';
                    break;
            }
            trace = contour(str);
        }
        while(c--)
            printf("%c", ans[c]);
        printf("\n");
    }
    return 0;
}
