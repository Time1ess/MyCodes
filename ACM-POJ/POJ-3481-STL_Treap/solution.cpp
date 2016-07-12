// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-07-12 14:58
// Last modified: 2016-07-12 15:05
// Filename: solution.cpp
// Description:
#include <iostream>
#include <map>
using namespace std;

map<int, int> mp;
map<int, int>::iterator it;

int main()
{
    int N, num, pri;
    while(scanf("%d", &N)&&N!=0)
    {
        switch(N)
        {
            case 1:
                scanf("%d%d", &num, &pri);
                mp[pri] = num;
                break;
            case 2:
                if(mp.empty())
                {
                    printf("0\n");
                    break;
                }
                it = mp.end();
                --it;
                printf("%d\n", it->second);
                mp.erase(it);
                break;
            case 3:
                if(mp.empty())
                {
                    printf("0\n");
                    break;
                }
                printf("%d\n", mp.begin()->second);
                mp.erase(mp.begin());
                break;
        }
    }
    return 0;
}
