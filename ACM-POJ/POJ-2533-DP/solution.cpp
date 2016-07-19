// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-19 10:20
// Last modified: 2016-07-19 10:39
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N=1e3+10;
const int inf=1e4+1;

int binary_search(int s[], int key, int len)
{
    int left = 0, right = len, mid;
    while(left!=right)
    {
        mid = (left+right)>>1;
        if(key == s[mid])
            return mid;
        else if(key > s[mid])
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main()
{
    int a[N], s[N];
    int n;
    while(~scanf("%d", &n))
    {
        memset(a, 0, sizeof(a));
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        s[0] = -1;
        int len = 1, j;
        for(int i = 1; i <= n; i++)
        {
            s[len] = inf;
            j = binary_search(s, a[i], len);
            if(j == len)
                len++;
            s[j] = a[i];
        }
        printf("%d\n", len-1);
    }
    return 0;
}
