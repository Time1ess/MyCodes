class Solution {
public:
    /**
     * @param str: str: the given string
     * @return: char: the first unique character in a given string
     */
    char firstUniqChar(string &str) {
        // Write your code here
        vector<int> cnts(256, 0);
        int n = str.length();
        for(int i = 0; i < n; i++)
            cnts[str[i]]++;
        for(int i = 0; i < n; i++)
            if(cnts[str[i]] == 1)
                return str[i];
        return '0';
    }
};
