// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-21 10:53
// Last modified: 2016-07-21 11:34
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

int map[155][15];
int tri[12] = {0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};
int dp[2][59049];
int pre[15], now[15];
int n, m;

int getten(int a[])
{
    int ans=0;
    for(int i = 1; i <= m; i++)
        ans += tri[i]*a[i];
    return ans;
}

void gettri(int k, int a[])
{
    for(int i = 1; i <= m; i++)
    {
        a[i] = k%3;
        k /= 3;
    }
}

void dfs(int i, int j, int last, int key)
{
    int k;
    dp[i%2][key] = max(dp[i%2][key], last);
    if(j >= m)
        return;
    if(!pre[j]&&!pre[j+1]&&!now[j]&&!now[j+1])
    {
        now[j] = now[j+1] = 2;
        k = getten(now);
        dfs(i, j+2, last+1, k);
        now[j] = now[j+1] = 0;
    }
    if(j<m-1&&!now[j]&&!now[j+1]&&!now[j+2])
    {
        now[j] = now[j+1] = now[j+2] = 2;
        k = getten(now);
        dfs(i, j+3, last+1, k);
        now[j] = now[j+1] = now[j+2] = 0;
    }
    dfs(i, j+1, last, key);
    return;
}


int main()
{
    int nn, k, a, b, tmp, ans;
    scanf("%d", &nn);
    while(nn--)
    {
        scanf("%d %d %d", &n, &m, &k);
        memset(dp, -1, sizeof(dp));
        memset(map, 0, sizeof(map));
        memset(pre, 0, sizeof(pre));
        memset(now, 0, sizeof(now));
        for(int i = 1; i <= k; i++)
        {
            scanf("%d %d", &a, &b);
            map[a][b] = 1;
        }
        for(int i = 1; i <= m; i++)
            pre[i] = map[1][i]+1;
        tmp = getten(pre);
        dp[1][tmp] = 0;
        for(int i = 2; i <= n; i++)
        {
            for(int j = 0; j < tri[m+1]; j++)
                dp[i%2][j] = -1;
            for(int j = 0; j < tri[m+1]; j++)
            {
                if(dp[(i+1)%2][j] == -1)
                    continue;
                gettri(j, pre);
                for(int t = 1; t <= m; t++)
                {
                    if(map[i][t])
                        now[t] = 2;
                    else
                        now[t] = max(pre[t]-1, 0);
                }
                tmp = getten(now);
                dfs(i, 1, dp[(i+1)%2][j], tmp);
            }
        }
        ans = 0;
        for(int i = 0; i < tri[m+1]; i++)
            ans = max(ans, dp[n%2][i]);
        printf("%d\n", ans);
    }
    return 0;
}
