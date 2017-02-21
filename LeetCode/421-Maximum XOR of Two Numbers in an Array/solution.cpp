// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-02-21 17:04
// Last modified: 2017-02-21 17:04
// Filename: solution.cpp
// Description:
class Solution {
public:
    int max_XOR(vector<int> s0, vector<int> s1, int max_bit)
    {
        if(s0.size() == 0 || s1.size() == 0 || max_bit < 0)
            return 0;
        int mask = 1 << max_bit;
        vector<int> s00, s01, s10, s11;
        for(auto num: s0)
            if(mask & num)
                s01.push_back(num);
            else
                s00.push_back(num);
        for(auto num: s1)
            if(mask & num)
                s11.push_back(num);
            else
                s10.push_back(num);
        if((s01.size() == 0 && s11.size() == 0) || (s00.size() == 0 && s10.size() == 0))
            return max_XOR(s0, s1, max_bit-1);
        else
        {
            int a = max_XOR(s00, s11, max_bit-1);
            int b = max_XOR(s01, s10, max_bit-1);
            return mask + max(a, b);
        }
    }
    
    int findMaximumXOR(vector<int>& nums) {
        int size = nums.size();
        if(size <= 1)
            return 0;
        else if(size == 2)
            return nums[0] ^ nums[1];
        vector<int> s0, s1;
        int max=-0xffffff;
        for(auto num: nums)
            max = num > max? num : max;
        int max_bit = 0;
        while(max)
        {
            max_bit++;
            max >>= 1;
        }
        max_bit--;
        int mask;
        int ans;
        for(;max_bit; max_bit--)
        {
            mask = 1 << max_bit;
            for(auto num: nums)
                if(mask & num)
                    s1.push_back(num);
                else
                    s0.push_back(num);
            if(s0.size() != 0 && s1.size() != 0)
            {
                ans = 1 << max_bit;
                break;
            }
            s0.clear();
            s1.clear();
        }
        return ans + max_XOR(s0, s1, max_bit-1);
    }
};
