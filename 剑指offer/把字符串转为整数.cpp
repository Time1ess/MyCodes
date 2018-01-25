class Solution {
public:
    long long StrToIntCore(string &s, bool positive, int index)
    {
        long long ans = 0;
        int size = s.length();
        while(index < size)
        {
            if(s[index] >= '0' && s[index] <= '9')
            {
                ans = ans * 10 + (positive? 1 : -1) * (s[index] - '0');
                if(( positive && ans > (int)0x7fffffff) ||
                   (!positive && ans < (int)0x80000000))
                    return 0;
            }
            else
                return 0;
            index++;
        }
        return ans;
    }
    int StrToInt(string str) {
        int size = str.length();
        if(size == 0)
            return 0;
        bool positive = true;
        int index = 0;
        if(str[index] == '+')
        {
            positive = true;
            index++;
        }
        else if(str[index] == '-')
        {
            positive = false;
            index++;
        }
        long long ans = StrToIntCore(str, positive, index);
        return (int)ans;
    }
};
