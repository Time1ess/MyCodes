// Author: David
// Email: youchen.du@gmail.com
// Created: 2016-09-17 14:13
// Last modified: 2016-09-17 14:13
// Filename: solution.cpp
// Description:
class Solution {
public:
    Solution(vector<int> nums) {
        this->nums.resize(nums.size());
        for(int i=0; i < nums.size(); i++)
            this->nums[i] = nums[i];
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return this->nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> nums = this->nums;
        for(int i=nums.size()-1;i >= 0; i--)
        {
            swap(nums[i], nums[rand()%(i+1)]);
        }
        return nums;
    }
private:
    vector<int> nums;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */
