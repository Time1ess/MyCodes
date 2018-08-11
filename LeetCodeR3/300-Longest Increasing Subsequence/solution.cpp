class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> lis;
        for(auto x: nums) {
            auto it = upper_bound(lis.begin(), lis.end(), x-1);
            if(it == lis.end()) {
                lis.push_back(x);
            } else {
                *it = x;
            }
        }
        return lis.size();
    }
};
