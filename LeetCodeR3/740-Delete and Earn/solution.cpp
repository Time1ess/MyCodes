class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector<int> cnts(10001, 0);
        for (auto x : nums) {
            cnts[x]++;
        }
        
        int skip = 0, take = 0;
        for (int x = 1; x <= 10000; x++) {
            int tmp_take = skip + x * cnts[x];
            skip = max(skip, take);
            take = tmp_take;
        }
        return max(skip, take);
    }
};
