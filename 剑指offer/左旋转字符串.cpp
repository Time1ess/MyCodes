class Solution {
public:
    string LeftRotateString(string str, int n) {
        int size = str.length();
        if(size == 0 || n == 0)
            return str;
        if(n > 0)
            n = n % size;
        else
            while(n < 0)
                n += size;
        while(n--)
        {
            char t = str[0];
            for(int i = 1; i < size; i++)
                str[i-1] = str[i];
            str[size-1] = t;
        }
        return str;
    }
};
