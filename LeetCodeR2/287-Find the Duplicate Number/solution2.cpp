class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 1;
        int r = n;
        while(l < r)
        {
            int m = l + (r-l) / 2;
            int c = 0;
            for(auto x: nums)
                if(x <= m)
                    c++;
            if(c <= m)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};
