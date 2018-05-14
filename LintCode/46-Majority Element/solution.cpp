class Solution {
public:
    /*
     * @param nums: a list of integers
     * @return: find a  majority number
     */
    int partition(vector<int> &nums, int s, int e)
    {
        if(s == e)
            return s;
        int idx = s + rand() % (e - s);
        swap(nums[idx], nums[e]);
        int small = s - 1;
        for(int i = s; i < e; i++)
        {
            if(nums[i] < nums[e])
            {
                ++small;
                if(small != i)
                    swap(nums[small], nums[i]);
            }
        }
        ++small;
        swap(nums[small], nums[e]);
        return small;
    }
    int linear_search(vector<int> &nums, int s, int e, int k)
    {
        
        if(s == e)
            return nums[s];
        int idx = partition(nums, s, e);
        if(idx == k)
            return nums[idx];
        else if(idx < k)
            return linear_search(nums, idx + 1, e, k);
        else
            return linear_search(nums, s, idx - 1, k);
    }
    int majorityNumber(vector<int> &nums) {
        // write your code here
        int n = nums.size();
        return linear_search(nums, 0, n - 1, n / 2);
    }
};
