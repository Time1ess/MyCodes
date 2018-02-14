class Solution {
public:
    string roman(int &n, int k, char low, char mid, char high)
    {
        int c = n / k;
        n %= k;
        string s = "";
        if(c == 9)
            s = s + low + high;
        else if(c >= 5)
        {
            s = s + mid;
            s.append(c - 5, low);
        }
        else if(c == 4)
            s = s + low + mid;
        else
            s.append(c, low);
        return s;
    }
    string intToRoman(int num) {
        vector<char> romans{'I', 'V', 'X', 'L', 'C', 'D', 'M', ' ', ' '};
        string ans = "";
        int k = 1000;
        for(int i = romans.size() - 3; i >= 0; i -= 2, k /= 10)
            ans += roman(num, k, romans[i], romans[i+1], romans[i+2]);
        return ans;
    }
};
