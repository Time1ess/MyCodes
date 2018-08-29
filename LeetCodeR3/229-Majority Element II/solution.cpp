class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cnt0 = 0, cnt1 = 0, num0 = 0, num1 = 1;
        for (auto x : nums) {
            if (num0 == x) {
                cnt0++;
            } else if (num1 == x) {
                cnt1++;
            } else if (cnt0 == 0) {
                cnt0 = 1;
                num0 = x;
            } else if (cnt1 == 0) {
                cnt1 = 1;
                num1 = x;
            } else {
                cnt0--;
                cnt1--;
            }
        }
        cnt0 = cnt1 = 0;
        for (auto x : nums) {
            if (x == num0) {
                cnt0++;
            } else if (x == num1) {
                cnt1++;
            }
        }
        vector<int> ans;
        if (cnt0 * 3 > n) {
            ans.push_back(num0);
        }
        if (cnt1 * 3 > n) {
            ans.push_back(num1);
        }
        return ans;
    }
};
