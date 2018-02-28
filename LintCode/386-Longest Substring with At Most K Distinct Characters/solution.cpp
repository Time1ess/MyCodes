class Solution {
public:
    /*
     * @param s: A string
     * @param k: An integer
     * @return: An integer
     */
    int lengthOfLongestSubstringKDistinct(string &s, int k) {
        // write your code here
        int distinct = 0;
        unordered_map<char, int> cnts;
        int i = 0, j = 0;
        int ans = 0;
        while(i < s.length())
        {
            cnts[s[i]]++;
            if(cnts[s[i]] == 1)
                distinct++;
            while(distinct > k)
            {
                cnts[s[j]]--;
                if(cnts[s[j]] == 0)
                    distinct--;
                j++;
            }
            ans = max(ans, i - j + 1);
            i++;
        }
        return ans;
    }
};
