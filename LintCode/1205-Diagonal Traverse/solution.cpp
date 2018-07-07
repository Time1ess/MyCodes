class Solution {
public:
    /**
     * @param matrix: a 2D array
     * @return: return a list of integers
     */
    vector<int> findDiagonalOrder(vector<vector<int>> &matrix) {
        // write your code here
        int m = matrix.size();
        if(m == 0)
            return {};
        int n = matrix[0].size();
        if(n == 0)
            return {};
        vector<int> ans;
        bool should_reverse = false;
        for(int i = 0; i < m; i++) {
            vector<int> tmp;
            int x = i;
            int y = 0;
            while(x >= 0 && y < n)
                tmp.push_back(matrix[x--][y++]);
            if(should_reverse)
                reverse(tmp.begin(), tmp.end());
            should_reverse = !should_reverse;
            for(auto t : tmp)
                ans.push_back(t);
        }
        for(int j = 1; j < n; j++) {
            vector<int> tmp;
            int x = m - 1;
            int y = j;
            while(x >= 0 && y < n) {
                tmp.push_back(matrix[x--][y++]);
            }
            if(should_reverse)
                reverse(tmp.begin(), tmp.end());
            should_reverse = !should_reverse;
            for(auto t : tmp)
                ans.push_back(t);
        }
        return ans;
    }
};
