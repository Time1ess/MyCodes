// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-16 08:42
// Last modified: 2017-02-16 08:42
// Filename: solution.cpp
// Description:
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int diff_cnt[2];
        int ans=0;
        int size = nums.size();
        int finish_cnt;
        while(true)
        {
            finish_cnt = 0;
            diff_cnt[0] = diff_cnt[1] = 0;
            for(int i=0; i < size; i++)
            {
                if(nums[i] == 0)
                    finish_cnt++;
                diff_cnt[nums[i]&1]++;
                nums[i]>>=1;
            }
            if(finish_cnt == size)
                break;
            ans += diff_cnt[0]*diff_cnt[1];
        }
        return ans;
    }
};
