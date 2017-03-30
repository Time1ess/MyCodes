// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-30 10:47
// Last modified: 2017-03-30 11:45
// Filename: solution.cpp
// Description:
#include <bits/stdc++.h>

#define MAXN 10

using namespace std;

bool cmp(const int &a, const int &b)
{
    return a > b;
}

float discount[6] = {0, 0, 0.05, 0.1, 0.2, 0.25};

float cal(int *book_num, int (*dp)[10][10][10][10])
{
    int cnts[5];
    int zero = 0;
    sort(book_num, book_num + 5, cmp);
    for(int i = 0; i < 5; i++)
    {
        cnts[i] = book_num[i];
        zero |= cnts[i];
    }
    if(zero == 0)
        return 0;
    if(dp[cnts[0]][cnts[1]][cnts[2]][cnts[3]][cnts[4]] != 0)
        return dp[cnts[0]][cnts[1]][cnts[2]][cnts[3]][cnts[4]];
    float min_price = 1e9, tmin;
    for(int k = 5; k >= 1; k--)
    {
        if(cnts[k-1] >= 1)
        {
            for(int i = 0; i <= k-1; i++)
                cnts[i] -= 1;
            tmin = cal(cnts, dp) + k * 8 * (1 - discount[k]);
            for(int i = 0; i <= k-1; i++)
                cnts[i] += 1;
            min_price = min(min_price, tmin);
        }
    }
    dp[cnts[0]][cnts[1]][cnts[2]][cnts[3]][cnts[4]] = min_price;
    return min_price;
}


int main()
{
    int book_num[5];
    freopen("inputs.txt", "r", stdin);
    while(cin>>book_num[0])
    {
        int dp[MAXN][MAXN][MAXN][MAXN][MAXN] = {0};
        float min_price;
        for(int i = 1; i < 5; i++)
            cin>>book_num[i];
        min_price = cal(book_num, dp);
        cout<<min_price<<endl;
    }
    return 0;
}
