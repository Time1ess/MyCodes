class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int size_a = A.size(), size_b = B.size();
        int dp[size_a + 1][size_b + 1];
        memset(dp, 0, sizeof(dp));
        int max_length = 0;
        // dp[i][j]: Maximum length of array appears in A.sub(0, i) and B.sub(0, j)
        for(int i = 0; i <= size_a; i++)
            for(int j = 0; j <= size_b; j++)
                if(i != 0 && j != 0 && A[i - 1] == B[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    max_length = max(max_length, dp[i][j]);
                }
        return max_length;
    }
};
