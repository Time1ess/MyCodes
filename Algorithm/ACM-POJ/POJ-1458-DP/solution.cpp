// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-19 09:49
// Last modified: 2016-07-19 09:56
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

const int N = 1e3;

int dp[N][N] = {0};

int main()
{
    string s1, s2;
    int len1, len2;
    while(cin>>s1>>s2)
    {
        len1 = s1.length();
        len2 = s2.length();
        for(int i = 1; i <= len1; i++)
            for(int j = 1; j <= len2; j++)
            {
                if(s1[i-1] == s2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        cout<<dp[len1][len2]<<endl;
    }
    return 0;
}
