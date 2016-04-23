// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-08 21:34
// Last modified: 2016-04-08 21:51
// Filename: solution.cpp
// Description:
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;


int mymap[3000];
int items[2100];

int main()
{
    int CASE;
    int C;
    int P;
    int I;
    int k;
    cin>>CASE;
    for(int j=1;j<=CASE;j++)
    {
        memset(items, 0, sizeof(items));
        memset(mymap, 0, sizeof(mymap));
        cin>>C;
        cin>>I;
        for(int i=1;i<=I;i++)
            cin>>items[i];
        for(k=1;k<=I;k++)
        {
            if((C-items[k]>0)&&mymap[C-items[k]]!=0)
                break;
            mymap[items[k]]=k;
        }
        cout<<"Case #"<<j<<": "<<mymap[C-items[k]]<<" "<<k<<endl;
    }
    return 0;
}
