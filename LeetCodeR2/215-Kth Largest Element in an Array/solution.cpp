class Solution {
public:
    int partition(vector<int> &nums, int s, int e)
    {
        int pivot = s + rand() % (e - s);
        swap(nums[pivot], nums[e]);
        int large = s - 1;
        for(int i = s; i < e; i++)
        {
            if(nums[i] > nums[e])
            {
                large++;
                if(large != i)
                    swap(nums[i], nums[large]);
            }
        }
        large++;
        swap(nums[large], nums[e]);
        return large;
    }
    int linear_search(vector<int> &nums, int s, int e, int k)
    {
        if(s >= e)
            return nums[s];
        int p = partition(nums, s, e);
        if(p == k)
            return nums[p];
        else if(p > k)
            return linear_search(nums, s, p - 1, k);
        else
            return linear_search(nums, p + 1, e, k);
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return linear_search(nums, 0, n - 1, k - 1);
    }
};
