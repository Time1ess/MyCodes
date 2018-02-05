struct Compare
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second < b.second; // a comes before b, priority_queue output largest element, so b output first
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnts;
        for(auto x: nums)
            cnts[x]++;
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
        for(auto x: cnts)
            pq.push({x.first, x.second});
        vector<int> ans;
        while(k--)
        {
            auto top = pq.top();
            pq.pop();
            ans.push_back(top.first);
        }
        return ans;
    }
};
