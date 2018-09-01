class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> nums(n+1, 0);
        int p2 = 0, p3 = 0, p5 = 0;
        nums[0] = 1;
        for (int i = 1; i <= n; i++) {
            nums[i] = min(nums[p2] * 2, min(nums[p3] * 3, nums[p5] * 5));
            if (nums[i] == nums[p2] * 2) {
                p2++;
            }
            if (nums[i] == nums[p3] * 3) {
                p3++;
            }
            if (nums[i] == nums[p5] * 5) {
                p5++;
            }
        }
        return nums[n-1];
    }
};
