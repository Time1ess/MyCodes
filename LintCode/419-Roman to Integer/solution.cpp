class Solution {
public:
    /**
     * @param s: Roman representation
     * @return: an integer
     */
    int romanToInt(string &s) {
        // write your code here
        unordered_map<char, int> romans{
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000},
        };
        int ans = 0;
        int cur = 0;
        char leading = ' ';
        for(auto c: s)
        {
            if(leading == ' ')
            {
                cur = romans[c];
                leading = c;
            }
            else
            {
                if(romans[leading] < romans[c])
                {
                    leading = ' ';
                    cur = romans[c] - cur;
                    ans += cur;
                    cur = 0;
                }
                else
                {
                    ans += cur;
                    leading = c;
                    cur = romans[c];
                }
            }
        }
        ans += cur;
        return ans;
    }
};
