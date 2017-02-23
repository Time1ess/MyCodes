// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-23 09:36
// Last modified: 2017-02-23 09:36
// Filename: solution.cpp
// Description:
class Solution {
public:
    int arrangements(vector<int>& nums, int start, int end)
    {
        if(start > end)
            return 1;
        int ans = 0;
        for(int k=start; k <= end; k++)
        {
            swap(nums[start], nums[k]);
            if(start % nums[start] == 0 || nums[start] % start == 0)
                ans += arrangements(nums, start+1, end);
            swap(nums[start], nums[k]);
        }
        return ans;
    }
    
    int countArrangement(int N) {
        vector<int> nums;
        for(int i=0; i <= N; i++)
            nums.push_back(i);
        int ans = arrangements(nums, 1, N);
        return ans;
    }

};
