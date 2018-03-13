class Solution {
public:
    string toHex(int num) {
        const static string hex = "0123456789abcdef";
        string s = "";
        int cnt = 0;
        while(num && cnt++ < 8)
        {
            s = hex[num&15] + s;
            num >>= 4;
        }
        return s;
    }
};
