class Solution {
public:
    /**
     * @param matrix: List[List[int]]
     * @param k: a integer
     * @return: return a integer
     */
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        // write your code here
        int n = matrix.size();
        if(n == 0)
            return -1;
        int m = matrix[0].size();
        if(m == 0)
            return -1;
        int l = matrix[0][0], r = matrix[n-1][m-1];
        while(l < r) {
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
