// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-20 14:35
// Last modified: 2016-07-20 14:47
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=1505;
int father[N], child_num[N];
int dp[N][2];
int n;

void DP(int root)
{
    if(child_num[root] == 0)
    {
        dp[root][0] = 0;
        dp[root][1] = 1;
        return;
    }
    int dp1, dp0;
    dp1 = dp0 = 0;
    for(int i = 0; i < n; i++)
    {
        if(father[i] == root)
        {
            DP(i);
            dp1 += min(dp[i][0], dp[i][1]);
            dp0 += dp[i][1];
        }
    }
    dp[root][1] = dp1 + 1;
    dp[root][0] = dp0;
}


int main()
{
    while(~scanf("%d", &n))
    {
        memset(father, -1, sizeof(father));
        memset(child_num, 0, sizeof(child_num));
        memset(dp, 0, sizeof(dp));
        int f, num, child;
        int root = -1;
        for(int i = 0; i < n; i++)
        {
            scanf("%d:(%d)", &f, &num);
            child_num[f] = num;
            if(root == -1)
                root = f;
            while(num--)
            {
                scanf("%d", &child);
                father[child] = f;
                if(root == child)
                    root = f;
            }
        }
        DP(root);
        printf("%d\n", min(dp[root][0], dp[root][1]));
    }
    return 0;
}
