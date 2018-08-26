class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size();
        while (l + 1 < r) {
            int m = l + (r - l) / 2;
            if (nums[m] > nums[m-1]) {
                l = m;
            } else {
                r = m;
            }
        }
        return l;
    }
};
