// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-10-04 10:25
// Last modified: 2017-10-04 10:25
// Filename: solution.cpp
// Description:
class Solution {
private:
    int moves[8][2] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<vector<double>> dp(N, vector<double>(N, 1.0));
        for(int round = 0; round < K; round++)
        {
            vector<vector<double>> tmp_dp(N, vector<double>(N, 0));
            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                {
                    for(auto move: moves)
                    {
                        int ti = i + move[0];
                        int tj = j + move[1];
                        if(survive(N, ti, tj))
                            tmp_dp[i][j] += dp[ti][tj];
                    }
                }
            dp = tmp_dp;
        }
        return dp[r][c] / pow(8, K);
    }
    bool survive(int N, int r, int c)
    {
        if(r < 0 || r >= N || c < 0 || c >= N)
            return false;
        return true;
    }
};
