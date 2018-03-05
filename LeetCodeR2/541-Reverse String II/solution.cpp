class Solution {
public:
    void reverse(string &str, int s, int e)
    {
        int i = s, j = e - 1;
        while(i < j)
            swap(str[i++], str[j--]);
    }
    string reverseStr(string s, int k) {
        int n = s.length();
        for(int i = 0; i < n; i += 2 * k)
            reverse(s, i, min(i + k, n));
        return s;
    }
};
