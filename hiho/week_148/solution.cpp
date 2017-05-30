// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-04 15:46
// Last modified: 2017-05-04 15:46
// Filename: solution.cpp
// Description:
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1007

int a[MAX_N];

int main()
{
    int TASKS;
    cin>>TASKS;
    while(TASKS--)
    {
        int N, W, H, P, t;
        int sum = 0;
        cin>>N>>P>>W>>H;
        for(int i = 0; i < N; i++)
            cin>>a[i];
        int S = 1;
        while(true)
        {
            int char_per_line = W / (S+1), row_per_page = H / (S+1);
            int left = 0, right = P * row_per_page;
            for(int i = 0; i < N; i++)
                left += int(ceil(1.0 * a[i] / char_per_line));
            if(left > right)
                break;
            S++;
        }
        cout<<S<<endl;
    }
    return 0;
}
