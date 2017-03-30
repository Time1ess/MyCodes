// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-30 09:25
// Last modified: 2017-03-30 09:25
// Filename: solution.cpp
// Description:
class Solution {
public:
    int partition(vector<int> &nums, int s, int e)
    {
        int first = s, last = e;
        int key = nums[s];
        while(first < last)
        {
            while(first < last && nums[last] <= key)
                last--;
            nums[first] = nums[last];
            while(first < last && nums[first] >= key)
                first++;
            nums[last] = nums[first];
        }
        nums[first] = key;
        return first;
    }
    int k_largest(vector<int> &nums, int s, int e, int k)
    {
        if(s > e)
            return -1;
        int idx = partition(nums, s, e) + 1;
        if(idx == k)
            return nums[idx - 1];
        else if(idx < k)
            return k_largest(nums, idx, e, k);
        else
            return k_largest(nums, s, idx - 1, k);
    }
    int findKthLargest(vector<int>& nums, int k) {
        return k_largest(nums, 0, nums.size() - 1, k);
    }
};
