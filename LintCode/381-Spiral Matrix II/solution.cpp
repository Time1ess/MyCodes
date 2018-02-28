class Solution {
public:
    /**
     * @param n: An integer
     * @return: a square matrix
     */
    vector<vector<int>> generateMatrix(int n) {
        // write your code here
        vector<vector<int>> ans(n, vector<int>(n, 0));
        int cnt = 1;
        int s = 0, e = n - 1;
        while(s <= e)
        {
            for(int j = s; j <= e; j++)
                ans[s][j] = cnt++;
            if(s < e)
                for(int i = s + 1; i <= e; i++)
                    ans[i][e] = cnt++;
            if(s < e)
                for(int j = e - 1; j >= s; j--)
                    ans[e][j] = cnt++;
            if(s < e - 1)
                for(int i = e - 1; i >= s + 1; i--)
                    ans[i][s] = cnt++;
            s++,e--;
        }
        return ans;
    }
};
