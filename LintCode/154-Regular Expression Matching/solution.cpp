class Solution {
public:
    /**
     * @param s: A string 
     * @param p: A string includes "." and "*"
     * @return: A boolean
     */
    bool isMatch(string s, string p) {
        // write your code here
        int len_s = s.length(), len_p = p.length();
        vector<vector<bool>> dp(len_s+1, vector<bool>(len_p+1, false));
        dp[len_s][len_p] = true;
        // Empty s suffix, valid p
        for(int j = len_p - 1; j >= 1; j-= 2)
            if(p[j] != '*')
                break;
            else
                dp[len_s][j-1] = true;
        for(int i = len_s - 1; i >= 0; i--)
        {
            for(int j = len_p - 1; j >= 0; j--)
            {
                bool first_match = (i < len_s && (s[i] == p[j] || p[j] == '.'));
                if(j < len_p - 1 && p[j+1] == '*')
                    dp[i][j] = dp[i][j+2] || (first_match && dp[i+1][j]);
                else
                    dp[i][j] = dp[i+1][j+1] && first_match;
            }
        }
        return dp[0][0];
    }
};
