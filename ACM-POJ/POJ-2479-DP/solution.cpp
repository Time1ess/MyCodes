// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-19 09:42
// Last modified: 2016-07-19 09:47
// Filename: solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=5e5+10;

int a[N], left[N], right[N];

int main()
{
    int T;
    int n;
    scanf("%d", &T);
    while(T--)
    {
       scanf("%d", &n);
       for(int i = 0; i < n; i++)
           scanf("%d", &a[i]);
       left[0] = a[0];
       for(int i = 1; i < n; i++)
           if(left[i-1] < 0)
               left[i] = a[i];
           else
               left[i] = left[i-1]+a[i];
       for(int i = 1; i < n; i++)
           left[i] = max(left[i], left[i-1]);
       right[n-1] = a[n-1];
       for(int i = n-2; i >= 0; i--)
           if(right[i+1] < 0)
               right[i] = a[i];
           else
               right[i] = right[i+1]+a[i];
       for(int i = n-2; i >= 0; i--)
           right[i] = max(right[i], right[i+1]);
       int res = -100000000;
       for(int i = 1; i < n; i++)
           res = max(res, left[i-1] + right[i]);
       printf("%d\n", res);
    }
    return 0;
}
