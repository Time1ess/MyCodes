class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int total = 0;
        int n = nums.size();
        vector<int> bits(32, 0);
        for(int i = 0; i < n; i++)
        {
            int offset = 0;
            int x = nums[i];
            while(x)
            {
                if(x & 0x1 == 1)
                    bits[offset]++;
                x = x >> 1;
                offset++;
            }
        }
        for(auto x: bits)
            total += x * (n - x);
        return total;
    }
};
