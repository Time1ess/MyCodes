// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-06 21:54
// Last modified: 2017-07-06 21:54
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int mmin = 1e9, mmax = -1e9;
        int k = nums.size();
        int idx[k] = {0};
        for(int i = 0; i < k; i++)
        {
            pq.push(make_pair(nums[i][0], i));
            mmin = min(mmin, nums[i][0]);
            mmax = max(mmax, nums[i][0]);
            idx[i]++;
        }
        int tmin = mmin, tmax = mmax;
        while(!pq.empty())
        {
            pair<int, int> x = pq.top();
            pq.pop();
            if(nums[x.second].size() <= idx[x.second])
                break;
            int t = nums[x.second][idx[x.second]++];
            tmin = min(pq.top().first, t);
            tmax = max(tmax, t);
            pq.push(make_pair(t, x.second));
            if((tmax-tmin) < (mmax-mmin))
            {
                mmax = tmax;
                mmin = tmin;
            }
        }
        vector<int> ans;
        ans.push_back(mmin);
        ans.push_back(mmax);
        return ans;
    }
};
