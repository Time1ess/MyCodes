class Solution {
public:
    int partition(vector<int> &nums, int s, int e)
    {
        int p = rand() % (e - s) + s;
        swap(nums[p], nums[e]);
        int small = s - 1;
        for(int p = s; p < e; p++)
        {
            if(nums[p] < nums[e])
            {
                ++small;
                if(small != p)
                    swap(nums[small], nums[p]);
            }
        }
        small++;
        swap(nums[small], nums[e]);
        return small;
    }
    void quick_sort(vector<int> &nums, int s, int e)
    {
        if(s >= e)
            return;
        int idx = partition(nums, s, e);
        int size = nums.size();
        if(idx == size / 2)
            return;
        else if(idx > size / 2)
            quick_sort(nums, s, idx - 1);
        else
            quick_sort(nums, idx + 1, e);
    }
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        quick_sort(nums, 0, n - 1);
        return nums[n/2];
    }
};
