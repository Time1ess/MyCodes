class Solution {
public:
    /**
     * @param M: the 01 matrix
     * @return: the longest line of consecutive one in the matrix
     */
    int longestLine(vector<vector<int>> &M) {
        // Write your code here
        int n = M.size();
        if(n == 0)
            return 0;
        int m = M[0].size();
        if(m == 0)
            return 0;
        vector<vector<vector<int>>> cnts(n, vector<vector<int>>(m, vector<int>(4, 0)));
        int ans = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
            {
                if(M[i][j] == 1)
                {
                    cnts[i][j][0] = j > 0 ? cnts[i][j-1][0] + 1 : 1;
                    cnts[i][j][1] = i > 0 ? cnts[i-1][j][1] + 1 : 1;
                    cnts[i][j][2] = (i > 0 && j > 0) ? cnts[i-1][j-1][2] + 1 : 1;
                    cnts[i][j][3] = (i > 0 && j < m - 1) ? cnts[i-1][j+1][3] + 1 : 1;
                    for(int k = 0; k < 4; k++)
                        ans = max(ans, cnts[i][j][k]);
                }
                else
                    cnts[i][j][0] = cnts[i][j][1] = cnts[i][j][2] = cnts[i][j][3] = 0;
            }
        return ans;
    }
};
