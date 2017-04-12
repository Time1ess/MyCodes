// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 11:04
// Last modified: 2017-04-12 14:35
// Filename: solution.cpp
// Description:
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 1002

int main()
{
    int q, n, m, s, t;
    int a[MAXN];
    int dp[MAXN][MAXN]; // dp[i][j]: least succeed problems  
                        // for first i levels and failed j problems
    int level[MAXN][MAXN]; // level[i][j]: least succeed problems
                           // for level i and failed j problems
    cin>>q;
    while(q--)
    {
        cin>>n>>m>>s>>t;
        memset(dp, 0x7, sizeof(dp));
        for(int i = 1; i <= n; i++)
        {
            cin>>a[i];
            for(int x = 0; x <= m; x++)
                level[i][x] = max(0, int(ceil((1.0 * a[i] - x * t)/s)));
        }
        for(int j = 0; j <= m; j++)
            dp[0][j] = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 0; j <= m; j++)
                for(int x = 0; x <= int(ceil(1.0 * a[i] / t)); x++)
                    if(x <= j)
                        dp[i][j] = min(dp[i][j], dp[i-1][j-x] + level[i][x]);
        int mmin = 0x7fffffff;
        for(int j = 0; j <= m; j++)
            if((dp[n][j] + j) <= m)
                mmin = min(mmin, dp[n][j]);
        if(mmin == 0x7fffffff)
            cout<<"No"<<endl;
        else
            cout<<mmin<<endl;
    }
    return 0;
}
