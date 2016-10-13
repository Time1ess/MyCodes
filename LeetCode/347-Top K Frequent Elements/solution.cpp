// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-10-05 21:52
// Last modified: 2016-10-05 21:52
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;
        if(!nums.size())
            return ans;
        unordered_map<int, int> cnt;
        for(auto x:nums)
            cnt[x]++;
        vector<vector<int>> bucket(nums.size()+1);
        for(auto x:cnt)
            bucket[x.second].push_back(x.first);
        for(int i=bucket.size()-1; i>=0; i--)
        {
            for(int j=0; j<bucket[i].size(); j++)
            {
                ans.push_back(bucket[i][j]);
                if(ans.size()==k)
                    return ans;
            }
        }
        return ans;
    }
};
