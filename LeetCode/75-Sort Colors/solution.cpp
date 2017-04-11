// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-04-11 10:32
// Last modified: 2017-04-11 10:32
// Filename: solution.cpp
// Description:
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int cnts[3] = {0}, size = nums.size();
        for(auto x: nums)
            cnts[x]++;
        int i = 0;
        for(int j = 0; j < 3; j++)
            while(cnts[j]--)
                nums[i++] = j;
    }
};
