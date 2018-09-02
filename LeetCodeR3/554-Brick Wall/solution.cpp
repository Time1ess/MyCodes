class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> cnts;
        int m = wall.size();
        int ans = 0;
        for (auto row : wall) {
            int n = row.size();
            int len = 0;
            for (int i = 0; i < n - 1; i++) {
                len += row[i];
                cnts[len]++;
                ans = max(ans, cnts[len]);
            }
        }
        return m - ans;
    }
};
