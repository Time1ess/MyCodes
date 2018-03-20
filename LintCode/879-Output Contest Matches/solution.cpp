class Solution {
public:
    /**
     * @param n: a integer, denote the number of teams
     * @return: a string
     */
    string ContestMatch(vector<string> matches)
    {
        int n = matches.size();
        if(n == 1)
            return matches[0];
        vector<string> new_matches;
        for(int i = 0; i < n / 2; i++)
            new_matches.push_back("(" + matches[i] + "," + matches[n-1-i] + ")");
        return ContestMatch(new_matches);
    }
    string findContestMatch(int n) {
        // write your code here
        vector<string> matches;
        for(int i = 1; i <= n; i++)
            matches.push_back(to_string(i));
        return ContestMatch(matches);
    }
};
