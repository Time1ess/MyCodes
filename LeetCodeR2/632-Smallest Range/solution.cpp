typedef vector<int>::iterator vii;

struct Compare
{
    bool operator()(const pair<vii, vii> &a, const pair<vii, vii> &b)
    {
        return *(a.first) > *(b.first);
    }
};

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<pair<vii, vii>, vector<pair<vii, vii>>, Compare> pq;
        int k = nums.size();
        int low = INT_MAX, high = INT_MIN;
        for(int i = 0; i < k; i++)
        {
            low = min(low, nums[i][0]);
            high = max(high, nums[i][0]);
            pq.push({nums[i].begin(), nums[i].end()});
        }
        vector<int> ans = {low, high};
        while(pq.size() == k)
        {
            auto top = pq.top();
            pq.pop();
            ++top.first;
            if(top.first == top.second)
                break;
            pq.push(top);
            
            low = *(pq.top().first);
            high = max(high, *(top.first));
            if(high - low < ans[1] - ans[0])
                ans = {low, high};
        }
        return ans;
    }
};
