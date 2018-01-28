#include <iostream>
#include <vector>

using namespace std;


int main()
{
    int x, y;
    cin>>x>>y;
    vector<int> dp(y+1, 1);
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y+1; j++)
            dp[j] += j != 0 ? dp[j-1] : 0;
    cout<<dp[y]<<endl;
    return 0;
}
