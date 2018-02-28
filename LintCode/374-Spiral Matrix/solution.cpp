class Solution {
public:
    /**
     * @param matrix: a matrix of m x n elements
     * @return: an integer list
     */
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        // write your code here
        vector<int> ans;
        int m = matrix.size();
        if(m == 0)
            return ans;
        int n = matrix[0].size();
        if(n == 0)
            return ans;
        int left = 0, top = 0, right = n - 1, bottom = m - 1;
        while(left <= right && top <= bottom)
        {
            for(int j = left; j <= right; j++)
                ans.push_back(matrix[top][j]);
            if(bottom - top > 0)
                for(int i = top + 1; i <= bottom; i++)
                    ans.push_back(matrix[i][right]);
            if(bottom - top > 0 && right - left > 0)
                for(int j = right - 1; j >= left; j--)
                    ans.push_back(matrix[bottom][j]);
            if(bottom - top > 1 && right - left > 0)
                for(int i = bottom - 1; i >= top + 1; i--)
                    ans.push_back(matrix[i][left]);
            left++,right--,top++,bottom--;
        }
        return ans;
    }
};
