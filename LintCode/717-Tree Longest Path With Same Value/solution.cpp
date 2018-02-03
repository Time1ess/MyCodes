class Solution {
public:
    /*
     * @param : as indicated in the description
     * @param : as indicated in the description
     * @return: Return the number of edges on the longest path with same value.
     */
    int dfs(const vector<int> &A, unordered_map<int, vector<int>> &rels,
            vector<bool> &visited, int root, int label)
    {
        if(visited[root - 1] || A[root-1] != label)
            return 0;
        visited[root - 1] = true;
        int tmp = 0;
        for(auto next_root: rels[root])
            tmp = max(tmp, dfs(A, rels, visited, next_root, label));
        visited[root - 1] = false;
        return 1 + tmp;
    }
    int LongestPathWithSameValue(vector<int> &A, vector<int> &E) {
        // write your code here
        unordered_map<int, vector<int>> rels;
        
        int E_size = E.size();
        int A_size = A.size();
        vector<bool> visited(A_size, false);
        for(int i = 0; i < E_size; i+= 2)
        {
            rels[E[i+1]].push_back(E[i]);
            rels[E[i]].push_back(E[i+1]);
        }
        int ans = 0;
        for(int root = 1; root <= A_size; root++)
        {
            int tmp = dfs(A, rels, visited, root, A[root-1]) - 1;
            ans = max(ans, tmp);
        }
        return ans;
    }
};
