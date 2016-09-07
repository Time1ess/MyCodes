class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff=0;
        for(auto num:nums)
        diff^=num;
        //find last bit a diff b
        diff&=-diff;//or diff=(diff&(diff-1))^diff;

        vector<int> ans={0,0};
        for(auto num:nums)
        {
            //diff nums into two groups,as b&diff!=a&diff so a and b
            //would be seperated.
            if((num&diff)==0)
            {
                ans[0]^=num;
            }
            else
            {
                ans[1]^=num;
            }
        }
        return ans;
    }
};
