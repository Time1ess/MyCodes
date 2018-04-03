class Solution {
public:
    /**
     * @param s: Roman representation
     * @return: an integer
     */
    int romanToInt(string &s) {
        int n = s.length();
        if(n == 0)
            return 0;
        // write your code here
        unordered_map<char, int> romans{
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000},
        };
        int ans = romans[s.back()];
        for(int i = n-2; i >= 0; i--)
            if(romans[s[i]] < romans[s[i+1]])
                ans -= romans[s[i]];
            else
                ans += romans[s[i]];
        return ans;
    }
};
