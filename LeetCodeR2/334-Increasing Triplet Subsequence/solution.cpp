class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        vector<int> increasing;
        for(auto num : nums)
        {
            auto it = lower_bound(increasing.begin(), increasing.end(), num);
            if(it == increasing.end())
                increasing.push_back(num);
            else
                *it = num;
            if(increasing.size() == 3)
                return true;
        }
        return false;
    }
};
