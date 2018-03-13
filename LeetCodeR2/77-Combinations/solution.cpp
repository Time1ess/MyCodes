class Solution {
public:
    void combine(vector<vector<int>> &ans, vector<int> &current, int s, int n, int k)
    {
        if(k == 0)
        {
            ans.push_back(current);
            return;
        }
        if(s > n)
            return;
        combine(ans, current, s+1, n, k);
        current.push_back(s);
        combine(ans, current, s+1, n, k-1);
        current.pop_back();
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> current;
        combine(ans, current, 1, n, k);
        return ans;
    }
};
