// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-07-25 10:36
// Last modified: 2017-07-25 10:36
// Filename: solution2.cpp
// Description:
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int size = nums.size();
        int cnts[size] = {0};
        for(int i = 0; i < size; i++)
            cnts[nums[i] - 1]++;
        int duplicate, missing;
        for(int i = 0; i < size; i++)
            if(cnts[i] == 2)
                duplicate = i+1;
            else if(cnts[i] == 0)
                missing = i+1;
        return {duplicate, missing};
    }
};
