// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-25 09:15
// Last modified: 2017-02-25 09:15
// Filename: solution.cpp
// Description:
class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int ans = 0;
        int dist = 0;
        for(auto p1: points)
        {
            map<long long, int> equal_dist_cnt;
            for(auto p2: points)
            {
                if(p1 == p2)
                    continue;
                dist = pow(p1.first-p2.first, 2) + pow(p1.second-p2.second, 2);
                equal_dist_cnt[dist] ++;
            }
            for(auto x: equal_dist_cnt)
            {
                if(x.second > 1)
                    ans += x.second * (x.second - 1);
            }
        }
        return ans;
    }
};
