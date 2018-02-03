#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
 
int main()
{
    int m, n, k, l, r;
    cin>>n;
    map<int, vector<int> > ks;
    for(int i = 1; i <= n; i++)
    {
        cin>>k;
        ks[k].push_back(i);
    }
    cin>>m;
    while(m--)
    {
        cin>>l>>r>>k;
        auto lower = lower_bound(ks[k].begin(), ks[k].end(), l);
        auto upper = upper_bound(ks[k].begin(), ks[k].end(), r);
        cout<<upper-lower<<endl;
    }
    return 0;
}
