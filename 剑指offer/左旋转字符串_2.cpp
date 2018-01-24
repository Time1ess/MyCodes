class Solution {
public:
    void Reverse(string &str, int s, int e)
    {
        int size = str.size();
        while(s < e)
        {
            swap(str[s], str[e]);
            s++, e--;
        }
    }
    string LeftRotateString(string str, int n) {
        int size = str.length();
        if(size == 0 || n == 0)
            return str;
        if(n > 0)
            n = n % size;
        else
            while(n < 0)
                n += size;
        Reverse(str, 0, n - 1);
        Reverse(str, n, size - 1);
        Reverse(str, 0, size - 1);
        return str;
    }
};
