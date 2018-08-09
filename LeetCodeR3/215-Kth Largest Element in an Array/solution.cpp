class Solution {
public:
    int find_pivot(vector<int>& nums, int s, int e) {
        swap(nums[rand() % (e - s) + s], nums[e]);
        int large = s - 1;
        for(int idx = s; idx < e; idx++) {
            if(nums[idx] > nums[e]) {
                ++large;
                if(idx != large) {
                    swap(nums[large], nums[idx]);
                }
            }
        }
        ++large;
        swap(nums[large], nums[e]);
        return large;
    }
    int linear_search(vector<int>& nums, int s, int e, int k) {
        if(s >= e) {
            return nums[s];
        }
        int large = find_pivot(nums, s, e);
        if(large == k) {
            return nums[large];
        } else if(large > k) {
            return linear_search(nums, s, large - 1, k);
        } else {
            return linear_search(nums, large + 1, e, k);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return linear_search(nums, 0, n - 1, k - 1);
    }
};
