class Solution {
public:
    void backtrack(vector<vector<int>> &ans, vector<int> &current, int k, int n, int max_digit)
    {
        if(k == 0)
        {
            if(n == 0)
                ans.push_back(current);
            return;
        }
        for(int d = min(n, max_digit); d >= k; d--)
        {
            current.push_back(d);
            backtrack(ans, current, k-1, n - d, d - 1);
            current.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> current;
        backtrack(ans, current, k, n, 9);
        return ans;
    }
};
