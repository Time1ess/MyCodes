class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        if (n == 0) {
            return 0;
        }
        vector<int> min_sum = triangle[n-1];
        for (int i = n - 2; i >= 0; i--) {
            int k = triangle[i].size();
            vector<int> tmp(k, 0);
            for (int j = 0; j < k; j++) {
                tmp[j] = triangle[i][j] + min(min_sum[j], min_sum[j+1]);
            }
            min_sum = tmp;
        }
        return min_sum[0];
    }
};
