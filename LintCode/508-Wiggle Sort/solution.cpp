class Solution {
public:
    /*
     * @param nums: A list of integers
     * @return: nothing
     */
    int partition(vector<int> &nums, int s, int e)
    {
        int pivot = s + rand() % (e - s);
        swap(nums[e], nums[pivot]);
        int small = s - 1;
        for(int i = s; i < e; i++)
        {
            if(nums[i] < nums[e])
            {
                ++small;
                if(small != i)
                    swap(nums[i], nums[small]);
            }
        }
        ++small;
        swap(nums[small], nums[e]);
        return small;
    }
    void qsort(vector<int> &nums, int s, int e)
    {
        if(s >= e)
            return;
        int pivot = partition(nums, s, e);
        qsort(nums, s, pivot - 1);
        qsort(nums, pivot+1, e);
    }
    void wiggleSort(vector<int> &nums) {
        // write your code here
        qsort(nums, 0, nums.size() - 1);
        int n = nums.size();
        for(int i = 1; i+1 < n; i += 2)
            swap(nums[i], nums[i+1]);
    }
};
