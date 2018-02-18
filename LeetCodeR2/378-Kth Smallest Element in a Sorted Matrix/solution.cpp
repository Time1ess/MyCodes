class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int l = matrix[0][0], r = matrix[n-1][n-1];
        while(l < r)
        {
            int m = l + (r - l) / 2;
            int cnt = 0;
            for(auto row: matrix)
                cnt += upper_bound(row.begin(), row.end(), m) - row.begin();
            if(cnt < k)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }
};
