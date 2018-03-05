bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        int n = points.size();
        if(n == 0)
            return 0;
        else if(n == 1)
            return 1;
        sort(points.begin(), points.end(), cmp);
        pair<int, int> current = points[0], tmp;
        int ans = 1;
        for(int i = 1; i < n; i++)
        {
            tmp = points[i];
            if(tmp.first > current.second)
            {
                ans++;
                current = tmp;
            }
            else
                current.second = min(current.second, tmp.second);
        }
        return ans;
    }
};
