class Solution {
public:
    /*
     * @param num1: a non-negative integers
     * @param num2: a non-negative integers
     * @return: return sum of num1 and num2
     */
    string addStrings(string &num1, string &num2) {
        // write your code here
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        string s = "";
        int c = 0;
        int len1 = num1.length(), len2 = num2.length();
        int i = 0, j = 0;
        while(i < len1 || j < len2)
        {
            int t = (i<len1? num1[i]-'0' : 0) + (j<len2? num2[j]-'0' : 0) + c;
            if(t >= 10)
            {
                t %= 10;
                c = 1;
            }
            else
                c = 0;
            s.append(to_string(t));
            i++, j++;
        }
        if(c == 1)
            s.push_back('1');
        reverse(s.begin(), s.end());
        return s;
    }
};
