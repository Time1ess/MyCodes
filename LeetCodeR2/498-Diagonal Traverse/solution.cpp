class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int m = matrix.size();
        if(m == 0)
            return ans;
        int n = matrix[0].size();
        if(n == 0)
            return ans;
        int r = 0, c = 0;
        cout<<endl;
        while(r < m && c < n)
        {
            while(r >= 0 && c < n)
                ans.push_back(matrix[r--][c++]);
            r++;
            if(c == n)
            {
                r++;
                c--;
            }
            while(r < m && c >= 0)
                ans.push_back(matrix[r++][c--]);
            c++;
            if(r == m)
            {
                c++;
                r--;
            }
            
        }
        return ans;
    }
};
