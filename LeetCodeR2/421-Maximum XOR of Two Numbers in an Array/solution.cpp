class Solution {
public:
    int max_XOR(vector<int> s0, vector<int> s1, int max_bit)
    {
        if(s0.empty() || s1.empty() || max_bit < 0)
            return 0;
        int mask = 1 << max_bit;
        vector<int> s00, s01, s10, s11;
        for(auto x: s0)
            if(mask & x)
                s01.push_back(x);
            else
                s00.push_back(x);
        for(auto x: s1)
            if(mask & x)
                s11.push_back(x);
            else
                s10.push_back(x);
        if((s01.empty() && s11.empty()) || (s00.empty() && s10.empty()))
            return max_XOR(s0, s1, max_bit-1);
        int a = max_XOR(s01, s10, max_bit-1);
        int b = max_XOR(s00, s11, max_bit-1);
        return mask + max(a, b);
    }

    int findMaximumXOR(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1)
            return 0;
        else if(n == 2)
            return nums[0] ^ nums[1];
        int max_num = INT_MIN;
        for(auto x: nums)
            max_num = max(max_num, x);
        vector<int> s0, s1;
        int max_bit = 0;
        while(max_num)
        {
            max_num>>=1;
            max_bit++;
        }
        max_bit--;
        int mask;
        int ans;
        for(;max_bit;max_bit--)
        {
            mask = 1 << max_bit;
            for(auto x: nums)
                if(x & mask)
                    s1.push_back(x);
                else
                    s0.push_back(x);
            if(!s1.empty() && !s0.empty())
            {
                ans = mask;
                break;
            }
            s1.clear();
            s0.clear();
        }
        return ans + max_XOR(s0, s1, max_bit-1);
    }
};
