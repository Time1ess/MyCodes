// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-10 08:35
// Last modified: 2017-10-10 08:35
// Filename: solution.cpp
// Description:
class NumArray {
private:
    vector<int> prefix_sum;
public:
    NumArray(vector<int> nums) {
        int sum = 0;
        prefix_sum.push_back(sum);
        for(int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            prefix_sum.push_back(sum);
        }
    }
    
    int sumRange(int i, int j) {
        return prefix_sum[j+1] - prefix_sum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
