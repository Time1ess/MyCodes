class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> lis;
        for(auto num: nums)
        {
            auto it = lower_bound(lis.begin(), lis.end(), num);
            if(it == lis.end())
                lis.push_back(num);
            else
                *it = num;
        }
        return lis.size();
    }
};
