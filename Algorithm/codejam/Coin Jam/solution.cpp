// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-04-09 11:13
// Last modified: 2016-04-09 13:50
// Filename: solution.cpp
// Description:
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

bool is_prime(int u)
{
    if(u==0||u==1)
        return 0;
    if(u==2)
        return true;
    if(u%2==0)
        return false;
    for(int i=3;i<=sqrt(u);i+=2)
        if(u%i==0)
            return false;
    return true;
}


int main()
{
}

