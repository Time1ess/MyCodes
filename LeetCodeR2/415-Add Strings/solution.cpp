class Solution {
public:
    string addStrings(string num1, string num2) {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        string ans = "";
        int i = 0, j = 0, n = num1.length(), m = num2.length();
        int c = 0;
        while(i < n || j < m)
        {
            int t = (i < n ? num1[i++] - '0': 0) + (j < m ? num2[j++] - '0': 0) + c;
            if(t >= 10)
            {
                t %= 10;
                c = 1;
            }
            else
                c = 0;
            ans.push_back('0' + t);
        }
        if(c == 1)
            ans.push_back('0' + 1);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
