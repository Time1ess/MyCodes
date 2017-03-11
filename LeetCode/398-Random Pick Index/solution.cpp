// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-11 09:35
// Last modified: 2017-03-11 09:35
// Filename: solution.cpp
// Description:
class Solution {
public:
    vector<int> n;
    Solution(vector<int> nums) {
        n = nums;
        srand(time(0));
    }
    
    int pick(int target) {
        int count = 0, res = -1;
        for(int i = 0; i < n.size(); i++)
        {
            if(target != n[i])
                continue;
            else if(!(rand() % (++count)))
                res = i;
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */
