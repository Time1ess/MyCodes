// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-08-02 10:38
// Last modified: 2016-08-02 12:01
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=70;

int s[N];
bool used[N];

int num;
int sum, tar, stick_num, mmax=-1;

bool cmp(const int &p, const int &q)
{
    return p>q?true:false;
}

bool DFS(int stick, int len, int pos)
{
    if(stick_num==stick)
        return true;
    for(int i=pos+1; i < num; i++)
    {
        if(used[i])
            continue;
        if(len+s[i]==tar)
        {
            used[i] = true;
            if(DFS(stick+1, 0, -1))
                return true;
            used[i] = false;
            return false;
        }
        else if(len+s[i]<tar)
        {
            used[i] = true;
            if(DFS(stick, len+s[i], i))
                return true;
            used[i] = false;
            // ** prune **
            // if s[i] does not fit, and len == 0, means s[i] is not avail-
            // able for all, because s[i] is the maximum in the unused set.
            // whenever try to compose another stick, s[i] will be the first
            // to select.
            if(len==0)
                return false;
            // ** prune **
            // if s[i] does not fit, then all sticks has the same lenth of
            // s[i] does not fit.
            while(s[i]==s[i+1])i++;
        }
    }
    return false;
}

int main()
{
    while(scanf("%d", &num)&&num)
    {
        sum = 0;
        mmax = -1;
        for(int i=0; i < num; i++)
        {
            scanf("%d", &s[i]);
            sum += s[i];
            mmax = mmax>s[i]?mmax:s[i];
        }
        sort(s, s+num, cmp);
        for(tar=mmax;tar<=sum;tar++)
        {
            if(sum%tar==0)
            {
                stick_num = sum/tar;
                memset(used, 0, sizeof(used));
                if(DFS(0, 0, -1))
                {
                    printf("%d\n", tar);
                    break;
                }
            }
        }
    }
    return 0;
}
