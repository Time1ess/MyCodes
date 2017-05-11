// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-05-11 09:05
// Last modified: 2017-05-11 09:05
// Filename: solution.cpp
// Description:
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        int p1, p2, cnt, last;
        p1 = 0;
        p2 = 1;
        cnt = 1;
        last = nums[0];
        while(p2 < nums.size())
        {
            if(last == nums[p2] && cnt)
            {
                cnt--;
                nums[++p1] = nums[p2];
            }
            else if(last != nums[p2])
            {
                last = nums[p2];
                nums[++p1] = nums[p2];
                cnt = 1;
            }
            p2++;
        }
        return p1+1;
    }
};
