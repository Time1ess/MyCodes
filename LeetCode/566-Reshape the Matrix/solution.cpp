// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-01 12:41
// Last modified: 2017-05-01 12:41
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        int oldr, oldc, j, cnt, tr, tc;
        oldr = nums.size();
        oldc = nums[0].size();
        if(oldr * oldc != r * c)
            return nums;
        vector<vector<int>> ans(r, vector<int>(c));
        cnt = 0;
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                tr = cnt / oldc;
                tc = cnt % oldc;
                ans[i][j] = nums[tr][tc];
                cnt++;
            }
        }
        return ans;
    }
};
