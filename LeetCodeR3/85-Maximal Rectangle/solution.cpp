class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        vector<int> height(n + 1, 0);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            stack<int> s;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    height[j]++;
                } else {
                    height[j] = 0;
                }
            }
            for (int j = 0; j < n + 1; j++) {
                while (!s.empty() && height[s.top()] >= height[j]) {
                    int idx = s.top();
                    s.pop();
                    ans = max(ans, height[idx] * (s.empty() ? j : (j - s.top() - 1)));
                }
                s.push(j);
            }
        }
        return ans;
    }
};
