#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}

int main()
{
    int n;
    cin>>n;
    vector<pair<int, int>> points;
    for(int i = 0; i < n; i++)
    {
        int x, y;
        cin>>x>>y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), cmp);
    vector<pair<int, int>> ans;
    int cur_y = -1;
    for(int i = n - 1; i >= 0; i--)
    {
        if(points[i].second > cur_y)  // No overlap
        {
            cur_y = points[i].second;
            ans.push_back(points[i]);
        }
    }
    for(int i = ans.size() - 1; i >= 0; i--)
        cout<<ans[i].first<<" "<<ans[i].second<<endl;
    return 0;
}
