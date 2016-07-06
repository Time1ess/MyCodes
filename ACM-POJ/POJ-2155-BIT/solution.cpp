// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-06 10:10
// Last modified: 2016-07-06 10:10
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

using namespace std;

#define ll long long
#define N 1010

int c[N][N];
int x1, y1, x2, y2;
int n, t;

int lowbit(int n)
{
    return n&(-n);
}

void update(int x, int y)
{
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            c[i][j] ^= 1;
}

int query(int x, int y)
{
    int ans=0;
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=n;j+=lowbit(j))
            ans += c[i][j];
    return ans&1;
}

int main()
{
    int CASE;
    char s[3];
    scanf("%d", &CASE);
    while(CASE--)
    {
        scanf("%d %d", &n, &t);
        memset(c, 0 , sizeof(c));
        for(int zz=1;zz<=t;zz++)
        {
            scanf("%s", s);
            if(s[0]=='C')
            {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                update(x1-1, y1-1);
                update(x2, y2);
                update(x2, y1-1);
                update(x1-1, y2);
            }
            else if(s[0]=='Q')
            {
                scanf("%d%d", &x1, &y1);
                printf("%d\n", query(x1, y1));
            }
        }
        printf("\n");
    }
    return 0;
}
