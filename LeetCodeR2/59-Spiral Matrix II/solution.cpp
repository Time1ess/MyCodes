class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n, vector<int>(n, 0));
        int k = 1;
        int s = 0, e = n - 1;
        while(s <= e)
        {
            for(int j = s; j <= e; j++)
                ans[s][j] = k++;
            if(e - s > 0)  // More than one row
                for(int i = s + 1; i <= e; i++)
                    ans[i][e] = k++;
            if(e - s > 0)  // More than one col
                for(int j = e - 1; j >= s; j--)
                    ans[e][j] = k++;
            if(e - s > 1)
                for(int i = e - 1; i >= s + 1; i--)
                    ans[i][s] = k++;
            s++, e--;
        }
        return ans;
    }
};
