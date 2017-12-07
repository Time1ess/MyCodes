class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int gains[100002] = {0};
        int max_num = 0;
        for(auto x: nums)
        {
            gains[x]++;
            max_num = max(max_num, x);
        }
        int ans = 0, dpm1 = 0, dpm2 = 0;
        for(int i = 1; i < 100001; i++)
        {
            ans = max(dpm2 + gains[i] * i, dpm1);
            dpm2 = dpm1;
            dpm1 = ans;
            if(i == max_num)
                break;
        }
        return ans;
    }
};
