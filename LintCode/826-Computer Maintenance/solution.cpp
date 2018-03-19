bool cmp(const Point &a, const Point &b)
{
    return a.y < b.y;
}

class Solution {
public:
    /**
     * @param n: the rows of matrix
     * @param m: the cols of matrix
     * @param badcomputers: the bad computers 
     * @return: The answer
     */
    int maintenance(int n, int m, vector<Point> &badcomputers) {
        // Write your code here
        if(n == 0)
            return 0;
        vector<int> dp(2, 0);
        vector<vector<Point>> lines(n, vector<Point>());
        for(auto p: badcomputers)
            lines[p.x].push_back(p);
        for(int i = 0; i < n; i++)
        {
            int left_most = INT_MAX, right_most = -1;
            for(auto p: lines[i])
            {
                left_most = min(left_most, p.y);
                right_most = max(right_most, p.y);
            }
            if(i == 0)
            {
                if(right_most != -1)
                    dp[0] = 2 * right_most;
                dp[1] = m - 1;
                continue;
            }
            if(right_most == -1)
            {
                dp[0] += 1;
                dp[1] += 1;
                continue;
            }
            int last_dp_0 = dp[0], last_dp_1 = dp[1];
            // left -> left, right -> left
            dp[0] = 1 + min(last_dp_0 + 2 * right_most, last_dp_1 + m - 1);
            // left -> right, right -> right
            dp[1] = 1 + min(last_dp_1 + 2 * (m - 1 - left_most), last_dp_0 + m - 1);
        }
        return min(dp[0], dp[1]);
    }
};
