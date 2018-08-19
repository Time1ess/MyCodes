class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        int n = heights.size();
        stack<int> s;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (!s.empty() && heights[s.top()] > heights[i]) {
                int idx = s.top();
                s.pop();
                int width = s.empty() ? i : (i - s.top() - 1);
                ans = max(ans, width * heights[idx]);
            }
            s.push(i);
        }
        heights.pop_back();
        return ans;
    }
};
