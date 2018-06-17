class Solution {
public:
    /**
     * @param N: The number of integers
     * @return: The number of beautiful arrangements you can construct
     */
    void permutation(vector<int>& nums, int& ans, int idx, int n) {
        if(idx == n + 1) {
            ans++;
            return;
        }
        for(int i = idx; i <= n; i++) {
            swap(nums[i], nums[idx]);
            if(nums[idx] % idx == 0 || idx % nums[idx] == 0)
                permutation(nums, ans, idx+1, n);
            swap(nums[i], nums[idx]);
        }
    }
    int countArrangement(int N) {
        // Write your code here
        vector<int> nums(N + 1, 0);
        for(int i = 1; i <= N; i++)
            nums[i] = i;
        int ans = 0;
        permutation(nums, ans, 1, N);
        return ans;
    }
};
