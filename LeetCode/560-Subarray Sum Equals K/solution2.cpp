// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-01 13:06
// Last modified: 2017-05-01 13:06
// Filename: solution2.cpp
// Description:
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        int cnt = 0, sum = 0;
        umap[0] = 1;
        for(auto x: nums)
        {
            sum += x;
            cnt += umap[sum - k];
            umap[sum]++;
        }
        return cnt;
    }
};
