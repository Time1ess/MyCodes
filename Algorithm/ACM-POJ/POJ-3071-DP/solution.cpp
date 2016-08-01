// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-20 14:57
// Last modified: 2016-07-20 15:50
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=130;

double p[N][N];
double dp[130][8];

int main()
{
    int n, i, j, k, m;
    while(~scanf("%d", &n) && n != -1)
    {
        m = 1<<n;
        memset(dp, 0 ,sizeof(dp));
        for(i = 0; i < m; i++)
        {
            for(j = 0; j < m; j++)
                scanf("%lf", &p[i][j]);
            dp[i][0] = 1;
        }
        int ans;
        for(i = 1; i <= n; i++)
        {
            ans = 0;
            for(j = 0; j < m; j++)
            {
                double sum = 0;
                for(k = 1<<(i-1); k < 1<<i; k++)
                    sum += dp[k^j][i-1]*p[j][k^j];
                dp[j][i] = dp[j][i-1]*sum;
                if(dp[j][i]>dp[ans][i])
                    ans = j;
            }
        }
        printf("%d\n", ans+1);
    }
    return 0;
}
