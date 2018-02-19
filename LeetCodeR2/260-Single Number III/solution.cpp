class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int t = 0;
        for(auto x: nums)
            t ^= x;
        int first = 0, second = 0;
        while(t&(t-1))
            t &= t-1;
        for(auto x: nums)
            if(x & t)
                first ^= x;
            else
                second ^= x;
        return {first, second};
    }
};
