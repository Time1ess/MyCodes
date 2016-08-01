// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-05 14:38
// Last modified: 2016-07-06 10:10
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
using namespace std;

#define ll long long
#define N 1010

int A[N];
int x1, y1, x2, y2;
int n, t;
bool tree[N<<2][N<<2];
int ans;


void editY(int i, int l, int r, int j, int y1, int y2)
{
    if(l>=y1&&r<=y2)
    {
        tree[i][j] ^= 1;
        return;
    }
    int mid = (l+r)>>1;
    if(y2<=mid)
        editY(i, l, mid, j*2, y1, y2);
    else if(y1>mid)
        editY(i, mid+1, r, j*2+1, y1, y2);
    else
    {
        editY(i, l, mid, j*2, y1, y2);
        editY(i, mid+1, r, j*2+1, y1, y2);
    }
}

void editX(int i, int l, int r, int x1, int y1, int x2, int y2)
{
    if(l>=x1&&r<=x2)
    {
        editY(i, 1, n, 1, y1, y2);
        return;
    }
    int mid = (l+r)>>1;
    if(x2<=mid)
        editX(2*i, l, mid, x1, y1, x2, y2);
    else if(x1>mid)
        editX(2*i+1, mid+1, r, x1, y1, x2, y2);
    else
    {
        editX(2*i, l, mid, x1, y1, x2, y2);
        editX(2*i+1, mid+1, r, x1, y1, x2, y2);
    }
}

void queryY(int i, int l, int r, int j, int y)
{
   ans ^= tree[i][j];
   if(l==r)
       return;
   int mid = (l+r)>>1;
   if(y<=mid)
       queryY(i, l, mid, j*2, y);
   else
       queryY(i, mid+1, r, j*2+1, y);
}

void queryX(int i, int l, int r, int x, int y)
{
    queryY(i, 1, n, 1, y);
    if(l==r)
        return;
    int mid = (l+r)>>1;
    if(x<=mid)
        queryX(i*2, l, mid, x, y);
    else
        queryX(i*2+1, mid+1, r, x, y);
}

int main()
{
    int CASE;
    char c[3];
    scanf("%d", &CASE);
    while(CASE--)
    {
        memset(tree, 0, sizeof(tree));
        scanf("%d%d", &n, &t);

        for(int zz=1;zz<=t;zz++)
        {
            scanf("%s", c);
            if(c[0]=='C')
            {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                editX(1, 1, n, x1, y1, x2, y2);
            }
            else if(c[0]=='Q')
            {
                ans = 0;
                scanf("%d%d", &x1, &y1);
                queryX(1, 1, n, x1, y1);
                printf("%d\n", ans);
            }
        }
        if(CASE)
            printf("\n");
    }
    return 0;
}
