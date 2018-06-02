class Solution {
public:
    /**
     * @param height: A list of integer
     * @return: The area of largest rectangle in the histogram
     */
    int largestRectangleArea(vector<int> &height) {
        // write your code here
        height.push_back(0);
        stack<int> s;
        int ans = 0;
        for (int i = 0; i < height.size(); i++) {
            while (!s.empty() && height[s.top()] > height[i]) {
                int idx = s.top();
                s.pop();
                int width = s.empty() ? i : (i - s.top() - 1);
                ans = max(ans, height[idx] * width);
            }
            s.push(i);
        }
        return ans;
    }
};
