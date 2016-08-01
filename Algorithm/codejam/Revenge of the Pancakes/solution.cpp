// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-09 09:58
// Last modified: 2016-04-09 10:38
// Filename: solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;


char s[110];
int len;

void reverse(int start,int end)
{
    if(start>end)
        return;
    char tmp;
    for(int i=start;i<=(end-start)/2;i++)
    {
        tmp=s[i]=='+'?'-':'+';
        s[i]=s[end-i]=='+'?'-':'+';
        s[end-i]=tmp;
    }
}

int length(char *s)
{
    int i;
    while(s[i]!='\0')i++;
    return i;
}

int check_valid(char *s)
{
    for(int i=0;s[i]!='\0';i++)
        if(s[i]=='-')
            return 0;
    return 1;
}

int find_min()
{
    int ans=0;
    while(!check_valid(s))
    {
        int plus_end=len-1;
        while(plus_end>=0&&s[plus_end]=='+')plus_end--;
        if(s[0]=='-')
        {
            reverse(0,plus_end);
        }
        else
        {
            int same=0;
            while(same<len&&s[same]=='+')same++;
            reverse(0,same-1);
        }
        ans++;
    }
    return ans;

}


int main()
{
    int T;
    scanf("%d",&T);
    for(int cc=1;cc<=T;cc++)
    {
        int ans=0;
        scanf("%s",s);
        len=length(s);
        ans=find_min();

        printf("Case #%d: %d\n",cc,ans);
    }
    return 0;
}
