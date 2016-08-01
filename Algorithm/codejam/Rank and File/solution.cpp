// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-16 10:04
// Last modified: 2016-04-16 10:18
// Filename: solution.cpp
// Description:
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;


#define SIZE 60

int main()
{
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        int N;
        map<int,int> mm;
        scanf("%d", &N);
        int t;

        for(int j=1;j<=N*(2*N-1);j++)
        {
            scanf("%d",&t);
            mm[t]++;
        }
        cout<<"Case #"<<i<<": ";
        for(map<int,int>::iterator x=mm.begin();x!=mm.end();x++)
        {
            if(x->second%2!=0)
            {
                cout<<x->first<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}

