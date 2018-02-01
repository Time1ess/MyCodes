class Solution {
public:
    /*
     * @param s: A string 
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    bool isMatch(string &s, string &p) {
        // write your code here
        int ssize = s.length(), psize = p.length();
        vector<vector<bool>> dp(ssize+1, vector<bool>(psize+1, false));
        dp[0][0] = true;
        for(int j = 1; j <= psize; j++)
            dp[0][j] = dp[0][j-1] && p[j-1] == '*';
        for(int i = 1; i <= ssize; i++)
            for(int j = 1; j <= psize; j++)
                if(p[j-1] == '*')
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                else
                    dp[i][j] = dp[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '?');
        return dp[ssize][psize];
    }
};
