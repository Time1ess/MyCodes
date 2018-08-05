class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 1, r = n - 1;
        while(l < r) {
            int m = l + (r - l) / 2;
            int cnt = 0;
            for(auto x: nums) {
                if(x <= m) {
                    cnt++;
                }
            }
            if(cnt <= m) {
                l = m + 1;
            } else if(cnt > m) {
                r = m;
            }
        }
        return l;
    }
};
