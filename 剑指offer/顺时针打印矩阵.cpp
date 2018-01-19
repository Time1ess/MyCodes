class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
		vector<int> ans;
        int m = matrix.size();
        if(m == 0)
            return ans;
        int n = matrix[0].size();
        if(n == 0)
            return ans;
        int l = 0, r = n - 1, t = 0, b = m - 1;
        while(l <= r && t <= b)
        {
            for(int k = l; k <= r; k++)  // left -> right
                ans.push_back(matrix[t][k]);
            if(t < b)
                for(int k = t + 1; k <= b; k++)  // top -> bottom
                    ans.push_back(matrix[k][r]);
            if(l < r && t < b)
                for(int k = r - 1; k >= l; k--)  // right -> left
                    ans.push_back(matrix[b][k]);
            if(l < r && t < b - 1)
                for(int k = b - 1; k >= t + 1; k--)  // bottom -> top
                    ans.push_back(matrix[k][l]);
            l++, r--, t++, b--;
        }
        return ans;
    }
};
