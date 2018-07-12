class Solution {
public:
    /**
     * @param temperatures: a list of daily temperatures
     * @return: a list of how many days you would have to wait until a warmer temperature
     */
    vector<int> dailyTemperatures(vector<int> &temperatures) {
        // Write your code here
        int n = temperatures.size();
        stack<int> indices;
        vector<int> ans(n, 0);
        for(int i = 0; i < n; i++) {
            while(!indices.empty() && temperatures[i] > temperatures[indices.top()]) {
                ans[indices.top()] = i - indices.top();
                indices.pop();
            }
            indices.push(i);
        }
        return ans;
    }
};
