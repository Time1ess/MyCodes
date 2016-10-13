// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-06 17:29
// Last modified: 2016-10-06 17:29
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;
        if(!nums.size())
            return ans;
        unordered_map<int,int> m;
        for(auto x:nums)
            m[x]++;
        priority_queue<pair<int,int>> pq;
        for(auto x:m)
            pq.push(make_pair(x.second,x.first));
        for(int i=1; i <= k; i++)
        {
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }
};
