class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans(num + 1, 0);
        int bit_mask = 1;
        int cnt = 1;
        for(int i = 1; i <= num; i++)
        {
            ans[i] = 1 + ans[i & (bit_mask-1)];
            if(--cnt == 0)
            {
                
                bit_mask <<= 1;
                cnt = bit_mask;
            }
        }
        return ans;
    }
};
