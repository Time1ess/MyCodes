class Solution {
public:
    int find(unordered_map<int, int> &parents, int x)
    {
        if(parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> parents;
        for(auto num: nums)
            parents[num] = num;
        for(auto x: nums)
        {
            if(parents.find(x+1) != parents.end())
                parents[x+1] = find(parents, x);
            if(parents.find(x-1) != parents.end())
                parents[x] = find(parents, x-1);
        }
        int ans = 0;
        for(auto x: nums)
            ans = max(ans, x - find(parents, x) + 1);
        return ans;
    }
};
