class Solution {
public:
    int find_parents(unordered_map<int, int>& parents, int x) {
        if (parents[x] != x) {
            parents[x] = find_parents(parents, parents[x]);
        }
        return parents[x];
    }
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> parents;
        for(auto x: nums) {
            parents[x] = x;
        }
        for(auto x: nums) {
            int p = find_parents(parents, x);
            if (parents.find(p-1) != parents.end()) {
                parents[p] = p-1;
            }
        }
        int ans = 0;
        for(auto x: nums) {
            int p = find_parents(parents, x);
            ans = max(ans, x - p + 1);
        }
        return ans;
    }
};
