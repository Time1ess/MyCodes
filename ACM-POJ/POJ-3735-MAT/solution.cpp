// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-28 09:10
// Last modified: 2016-07-28 10:12
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>

#define ll long long
const int MAXN=105;

struct Mat
{
    ll m[MAXN][MAXN];
};

int N,M,K;
Mat mat;

void setup_mat()
{
    char cmd[2];
    int i,j,x,y,t;
    memset(mat.m, 0, sizeof(mat.m));
    for(i=0;i<=N;i++)
        mat.m[i][i]=1;
    while(K--)
    {
        scanf("%s", cmd);
        if(cmd[0]=='g')
        {
            scanf("%d", &x);
            x--;
            mat.m[x][N]++;
        }
        else if(cmd[0]=='s')
        {
            scanf("%d %d", &x, &y);
            x--;
            y--;
            if(x!=y)
            {
                for(i=0;i<=N;i++)
                {
                    t = mat.m[x][i];
                    mat.m[x][i] = mat.m[y][i];
                    mat.m[y][i] = t;
                }
            }
        }
        else // e
        {
            scanf("%d", &x);
            x--;
            for(i=0;i<=N;i++)
                mat.m[x][i]=0;
        }
    }
}

Mat multi(Mat m1, Mat m2)
{
    Mat ans;
    memset(ans.m, 0, sizeof(ans.m));
    for(int i=0;i<=N;i++)
        for(int j=0;j<=N;j++)
            if(m1.m[i][j])
                for(int k=0;k<=N;k++)
                    ans.m[i][k] += m1.m[i][j]*m2.m[j][k];
    return ans;
}

Mat mat_multi(Mat m, int k)
{
    Mat ans;
    memset(ans.m, 0, sizeof(ans.m));
    for(int i=0;i<=N;i++)
        ans.m[i][i]=1;
    while(k)
    {
        if(k&1)
            ans=multi(ans, m);
        k>>=1;
        m=multi(m, m);
    }
    return ans;
}

int main()
{
    while(~scanf("%d %d %d", &N, &M, &K))
    {
        if(N==0&&M==0&&K==0)
            break;
        setup_mat();
        Mat ans;
        ans=mat_multi(mat, M);
        for(int i=0;i<N;i++)
            printf("%lld ", ans.m[i][N]);
        printf("\n");
    }
    return 0;
}
