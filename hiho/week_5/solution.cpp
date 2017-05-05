// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-05 14:36
// Last modified: 2017-05-05 14:53
// Filename: solution.cpp
// Description:
#include <bits/stdc++.h>
using namespace std;


int a[210][210] = {0};
int best[210][210] = {0};


void DFS(int n, int i, int j)
{
    if(best[i][j] != 0)
        return;
    if(i == n)
    {
        best[i][j] = a[i][j];
        return;
    }
    DFS(n, i+1, j);
    DFS(n, i+1, j+1);
    best[i][j] = a[i][j] + max(best[i+1][j], best[i+1][j+1]);
}


int main()
{
    int n;
    cin>>n;
    int ans = 0;
    for(int i = 1; i <= n; i++)
        for(int k = 1; k <= i; k++)
            cin>>a[i][k];
    DFS(n, 1, 1);
    cout<<best[1][1]<<endl;
    return 0;
}
