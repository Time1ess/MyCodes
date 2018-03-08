/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second;
}

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<pair<int, int>> s_indices;
        int n = intervals.size();
        for(int i = 0; i < n; i++)
            s_indices.push_back({i, intervals[i].start});
        sort(s_indices.begin(), s_indices.end(), cmp);
        vector<int> ans;
        for(int i = 0; i < n; i++)
        {
            pair<int, int> target = {-1, intervals[i].end - 1};
            auto it = upper_bound(s_indices.begin(), s_indices.end(), target, cmp);
            if(it == s_indices.end())
                ans.push_back(-1);
            else
                ans.push_back((*it).first);
        }
        return ans;
    }
};
