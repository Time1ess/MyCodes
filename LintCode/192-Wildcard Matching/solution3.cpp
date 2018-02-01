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
        vector<bool> dp(ssize+1, false);
        dp[0] = true;
        for(int j = 1; j <= psize; j++)
        {
            bool pre = dp[0];
            dp[0] = dp[0] && p[j-1] == '*';
            for(int i = 1; i <= ssize; i++)
            {
                bool tmp = dp[i];
                if(p[j-1] == '*')
                    dp[i] = dp[i] || dp[i-1];
                else
                    dp[i] = pre && (s[i-1] == p[j-1] || p[j-1] == '?');
                pre = tmp;
            }
        }
        return dp[ssize];
    }
};
