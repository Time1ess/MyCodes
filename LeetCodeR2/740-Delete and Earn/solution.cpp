class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector<int> buckets(10001, 0);
        for(auto x : nums)
            buckets[x] += x;
        int take_m1 = buckets[1], take_m2 = 0, skip_m2 = 0, skip_m1 = 0, take = 0, skip = 0;
        for(int i = 2; i < 10001; i++)
        {
            skip = max(skip_m1, take_m1);
            take = max(skip_m2, take_m2) + buckets[i];
            skip_m2 = skip_m1;
            skip_m1 = skip;
            take_m2 = take_m1;
            take_m1 = take;
        }
        return max(skip, take);
    }
};
