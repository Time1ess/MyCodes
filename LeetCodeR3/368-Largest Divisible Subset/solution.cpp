class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return {};
        } else if (n == 1) {
            return nums;
        }
        sort(nums.begin(), nums.end());
        vector<int> count(n, 0);
        vector<int> pre(n, -1);
        int mmax = 0, pos = -1;
        for (int i = 0; i < n; i++) {
            count[i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] % nums[j] == 0 && count[j] + 1 > count[i]) {
                    count[i] = count[j] + 1;
                    pre[i] = j;
                }
            }
            if (count[i] > mmax) {
                pos = i;
                mmax = count[i];
            }
        }
        vector<int> ans;
        while (pos != -1) {
            ans.push_back(nums[pos]);
            pos = pre[pos];
        }
        return ans;
    }
};
