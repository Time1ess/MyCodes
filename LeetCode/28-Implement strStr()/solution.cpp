class Solution {
public:
    vector<int> make_next(string s, int &size)
    {
        vector<int> next(size, -1);
        int k = -1;
        for(int i = 1; i < size; i++)
        {
            while(k > -1 && s[k+1] != s[i])
                k = next[k];
            if(s[k+1] == s[i])
                k += 1;
            next[i] = k;
        }
        return next;
    }
    int strStr(string haystack, string needle) {
        if(needle.size() == 0 || haystack == needle)
            return 0;
        int hsize = haystack.size(), nsize = needle.size();
        int k = -1;
        vector<int> next = make_next(needle, nsize);
        for(int i = 0; i < hsize; i++)
        {
            while(k > -1 && haystack[i] != needle[k+1])
                k = next[k];
            if(haystack[i] == needle[k+1])
                k += 1;
            if(k == nsize - 1)
                return i - nsize + 1;
        }
        return -1;
    }
};
