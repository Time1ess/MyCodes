// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-12 14:36
// Last modified: 2017-04-12 15:49
// Filename: solution2.cpp
// Description:
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 1002

struct Record
{
    int level;
    int score;
    Record()
    {
        this->level = 0;
        this->score = 0;
    }
    Record(int level, int score)
    {
        this->level = level;
        this->score = score;
    }
};

const Record& max(const Record &a, const Record &b)
{
    if(a.level > b.level)
        return a;
    else if(a.level == b.level)
        return a.score > b.score ? a : b;
    else
        return b;
}

int main()
{
    int q, n, m, s, t;
    int a[MAXN];
    Record dp[MAXN][MAXN];
    cin>>q;
    while(q--)
    {
        cin>>n>>m>>s>>t;
        memset(a, 0, sizeof(a));
        for(int i = 1; i <= n; i++)
            cin>>a[i];
        dp[0][0] = Record(1, 0);
        for(int j = 1; j <= m; j++)
        {
            Record r = dp[0][j-1];
            r.score += s;
            if(r.level <= n && a[r.level] <= r.score)
            {
                r.score = 0;
                r.level++;
            }
            dp[0][j] = r;
            r = dp[j-1][0];
            r.score += t;
            if(r.level <= n && a[r.level] <= r.score)
            {
                r.score = 0;
                r.level++;
            }
            dp[j][0] = r;
        }
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= m; j++)
            {
                Record rf = dp[i-1][j];
                rf.score += t;
                if(rf.level <= n && a[rf.level] <= rf.score)
                {
                    rf.score = 0;
                    rf.level++;
                }
                Record rs = dp[i][j-1];
                rs.score += s;
                if(rs.level <= n && a[rs.level] <= rs.score)
                {
                    rs.score = 0;
                    rs.level++;
                }
                dp[i][j] = max(rf, rs);
            }
        int minj = 1e7;
        for(int i = 0; i <= m; i++)
            for(int j = 0; j <= m; j++)
                if((i+j) == m && dp[i][j].level == n+1 && j < minj)
                    minj = j;
        if(minj == 1e7)
            cout<<"No"<<endl;
        else
            cout<<minj<<endl;
    }
    return 0;
}
