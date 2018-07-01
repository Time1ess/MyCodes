class Subset {
public:
    void backtrack(vector<int>& A, vector<vector<int>>& ans, vector<int>& current, int idx, int n) {
        if(idx == n) {
            if(!current.empty()) {
                ans.push_back(current);
            }
            return;
        }
        backtrack(A, ans, current, idx+1, n);
        current.push_back(A[idx]);
        backtrack(A, ans, current, idx+1, n);
        current.pop_back();
    }
    vector<vector<int> > getSubsets(vector<int> A, int n) {
        // write code here
        vector<vector<int>> ans;
        vector<int> current;
        backtrack(A, ans, current, 0, n);
        return ans;
    }
};
