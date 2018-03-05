class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> cands(5, 0);
        cands[0] = cands[1] = INT_MAX;  // min nums
        cands[2] = cands[3] = cands[4] = INT_MIN;  // max_nums
        for(auto x: nums)
        {
            if(x < cands[0])
            {
                cands[1] = cands[0];
                cands[0] = x;
            }
            else if(x < cands[1])
            {
                cands[1] = x;
            }
            if(x > cands[4])
            {
                cands[2] = cands[3];
                cands[3] = cands[4];
                cands[4] = x;
            }
            else if(x > cands[3])
            {
                cands[2] = cands[3];
                cands[3] = x;
            }
            else if(x > cands[2])
            {
                cands[2] = x;
            }
        }
        return max(cands[2] * cands[3] * cands[4], cands[0] * cands[1] * cands[4]);
    }
};
