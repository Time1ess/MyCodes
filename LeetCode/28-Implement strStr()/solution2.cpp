class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size() == 0)
            return 0;
        for(int i = 0; i < haystack.size(); i++)
            for(int j = 0; j < needle.size(); j++)
                if(i + j == haystack.size())
                    return -1;
                else if(haystack[i+j] != needle[j])
                    break;
                else if(j == needle.size() - 1)
                    return i;
        return -1;
    }
};
