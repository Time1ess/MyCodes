class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> cnts;
        for(auto num: nums)
            cnts[num]++;
        int ans = 0;
        for(auto p: cnts)
            if(cnts.count(p.first-1)>0)
                ans = max(ans, p.second + cnts[p.first-1]);
        return ans;
    }
};
