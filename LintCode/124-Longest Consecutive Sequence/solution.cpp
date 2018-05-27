class Solution {
public:
    /**
     * @param num: A list of integers
     * @return: An integer
     */
    int find(unordered_map<int, int>& parents, int x) {
        if (parents[x] != x)
            parents[x] = find(parents, parents[x]);
        return parents[x];
    }
    int longestConsecutive(vector<int> &num) {
        // write your code here
        unordered_map<int, int> parents;
        for (auto x: num)
            parents[x] = x;
        int ans = 0;
        for (auto x: num)
            if (parents.find(x-1) != parents.end())
                parents[x] = x - 1;
        for (auto x: num) {
            int px = find(parents, x);
            ans = max(ans, x - px + 1);
        }
        return ans;
    }
};
