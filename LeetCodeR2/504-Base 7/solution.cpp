class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0)
            return "0";
        bool neg = false;
        if(num < 0)
        {
            neg = true;
            num = -num;
        }
        string ans = "";
        while(num)
        {
            ans.push_back('0' + (num % 7));
            num /= 7;
        }
        reverse(ans.begin(), ans.end());
        return neg ? "-" + ans : ans;
    }
};
