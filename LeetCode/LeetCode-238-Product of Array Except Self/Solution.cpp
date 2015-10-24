class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int from_begin=1,from_end=1;
        int size=nums.size();
        vector<int> ans(size,1);
        for(int i=0;i<size;i++)
        {
            ans[i]*=from_begin;
            from_begin*=nums[i];
            ans[size-1-i]*=from_end;
            from_end*=nums[size-1-i];
        }
        return ans;
        
    }
};
