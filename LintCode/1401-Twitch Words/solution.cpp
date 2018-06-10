class Solution {
public:
    /**
     * @param str: the origin string
     * @return: the start and end of every twitch words
     */
    vector<vector<int>> twitchWords(string &str) {
        // Write your code here
        int n = str.length();
        vector<vector<int>> ans;
        int s = 0;
        while (s < n) {
            int e = s + 1;
            while (e < n && str[s] == str[e])
                e++;
            if (e - s >= 3)
                ans.push_back({s, e-1});
            s = e;
        }
        return ans;
    }
};
