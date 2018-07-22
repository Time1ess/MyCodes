class Solution {
public:
    /**
     * @param nums: a sorted array
     * @param a: 
     * @param b: 
     * @param c: 
     * @return: a sorted array
     */
    int trans(int x, int a, int b, int c) {
        return a * x * x + b * x + c;
    }
    vector<int> transform(vector<int>& nums, int n, int a, int b, int c) {
        vector<int> ans(nums.begin(), nums.end());
        for(int i = 0; i < n; i++) {
            ans[i] = trans(nums[i], a, b, c);
        }
        return ans;
    }
    vector<int> sortTransformedArray(vector<int> &nums, int a, int b, int c) {
        // Write your code here
        int n = nums.size();
        if(n == 0) {
            return {};
        }
        if(a == 0) {
            vector<int> ans = transform(nums, n, a, b, c);
            if(b < 0) {
                reverse(ans.begin(), ans.end());
            }
            return ans;
        }
        int m = -1.0 * b / (2 * a);
        int mmin = nums[0];
        int mmax = nums[n-1];
        if(m <= mmin) {
            vector<int> ans = transform(nums, n, a, b, c);
            if(a < 0) {
                reverse(ans.begin(), ans.end());
            }
            return ans;
        } else if(m >= mmax) {
            vector<int> ans = transform(nums, n, a, b, c);
            if(a > 0) {
                reverse(ans.begin(), ans.end());
            }
            return ans;
        }
        vector<int> ans;
        int l = 0, r = n - 1;
        while(l <= r) {
            int x = trans(nums[l], a, b, c);
            int y = trans(nums[r], a, b, c);
            if(a > 0) {
                if(x > y) {
                    ans.push_back(x);
                    l++;
                } else {
                    ans.push_back(y);
                    r--;
                }
            } else {
                if(x < y) {
                    ans.push_back(x);
                    l++;
                } else {
                    ans.push_back(y);
                    r--;
                }
            }
        }
        if(a > 0) {
            reverse(ans.begin(), ans.end());
        }
        return ans;
    }
};
