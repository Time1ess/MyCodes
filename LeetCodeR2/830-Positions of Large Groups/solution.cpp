class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        int n = S.length();
        int start_idx = 0;
        vector<vector<int>> ans;
        for (int i = 1; i <= n; i++) {
            if (i == n || S[i] != S[start_idx]) {
                if (i - start_idx >= 3)
                    ans.push_back({start_idx, i - 1});
                start_idx = i;
            }
        }
        return ans;
    }
};
