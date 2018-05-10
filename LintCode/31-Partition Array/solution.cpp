class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
    int partitionArray(vector<int> &nums, int k) {
        // write your code here
        int n = nums.size();
        int small = -1;
        for(int i = 0; i < n; i++)
        {
            if(nums[i] < k)
            {
                ++small;
                if(small != i)
                    swap(nums[i], nums[small]);
            }
        }
        ++small;
        return small;
    }
};
