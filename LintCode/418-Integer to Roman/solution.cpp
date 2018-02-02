class Solution {
public:
    /*
     * @param n: The integer
     * @return: Roman representation
     */
    string generate(int &n, int m, char low, char mid, char high)
    {
        int c;
        string s = "";
        if(n >= m)
        {
            c = n / m;
            if(c == 9)
                s = s + low + high;
            else if(c >= 5)
            {
                s = s + mid;
                s.append(c-5, low);
            }
            else if(c == 4)
                s = s + low + mid;
            else
                s.append(c, low);
            n %= m;
        }
        return s;
    }
    string intToRoman(int n) {
        // write your code here
        string s = "";
        int c = 0;
        const vector<char> romans{'I', 'V', 'X', 'L', 'C', 'D', 'M', ' ', ' '};
        int k = 1000;
        for(int i = romans.size() - 3; i >= 0; i-=2)
        {
            s += generate(n, k, romans[i], romans[i+1], romans[i+2]);
            k /= 10;
        }
        return s;
    }
};
