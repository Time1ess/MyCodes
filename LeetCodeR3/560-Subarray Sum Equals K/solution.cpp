class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0;
        unordered_map<int, int> sum_cnts;
        sum_cnts[0] = 1;
        int sum = 0;
        for(auto x: nums) {
            sum += x;
            ans += sum_cnts[sum-k];
            sum_cnts[sum]++;
        }
        return ans;
    }
};
