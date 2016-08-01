// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-19 10:08
// Last modified: 2016-07-19 10:10
// Filename: solution.cpp
// Description:
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

const int N=5e3+10;

int dp[2][N];

int main()
{
    string s1, s2;
    int n;
    while(cin>>n)
    {
        cin>>s1;
        s2 = s1;
        reverse(s2.begin(), s2.end());
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                dp[i%2][j] = max(dp[(i-1)%2][j], dp[i%2][j-1]);
                if(s1[i-1] == s2[j-1])
                {
                    int tmp = dp[(i-1)%2][j-1] + 1;
                    dp[i%2][j] = max(tmp, dp[i%2][j]);
                }
            }
        cout<<n-dp[n%2][n]<<endl;
    }
    return 0;
}

