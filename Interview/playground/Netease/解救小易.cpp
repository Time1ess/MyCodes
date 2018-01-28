#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, tmp;
    cin>>n;
    vector<int> xs, ys;
    for(int i = 0; i < 2 * n; i++)
    {
        cin>>tmp;
        if(i < n)
        	xs.push_back(tmp);
        else
            ys.push_back(tmp);
    }
    int dist = 2000;
    for(int i = 0; i < n; i++)
        dist = min(dist, xs[i] + ys[i] - 2);
    cout<<dist<<endl;
    return 0;
}
