class Solution {
public:
    /**
     * @param strs: A list of strings
     * @return: The longest common prefix
     */
    string longestCommonPrefix(vector<string> &strs, int l, int r)
    {
        if(l > r)
            return "";
        if(l == r)
            return strs[l];
        int m = l + (r - l) / 2;
        string left = longestCommonPrefix(strs, l, m);
        string right = longestCommonPrefix(strs, m + 1, r);
        int len1 = left.length(), len2 = right.length();
        for(int i = 0; i < min(len1, len2); i++)
            if(left[i] != right[i])
                return left.substr(0, i);
        return len1 > len2 ? right : left;
    }
    string longestCommonPrefix(vector<string> &strs) {
        // write your code here
        int n = strs.size();
        return longestCommonPrefix(strs, 0, n - 1);
    }
};
