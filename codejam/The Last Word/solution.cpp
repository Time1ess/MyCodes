// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-16 09:20
// Last modified: 2016-04-16 09:25
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define N 1010

char s[N], ans[N];

int main()
{
    int T;
    scanf("%d",&T);
    for(int i =1;i<=T;i++)
    {
        scanf("%s", s);
        int len = strlen(s);
        int li = 0, ri = len -1;
        for(int j = len-1;j>=0;--j)
        {
            bool right = false;
            for(int k=0;k<j;++k)
            {
                if(s[k]>s[j])
                {
                    right = true;
                    break;
                }
            }
            if(right)
                ans[ri--]=s[j];
            else
                ans[li++]=s[j];
        }
        ans[len]='\0';
        printf("Case #%d: %s\n", i, ans);
    }
    return 0;
}

