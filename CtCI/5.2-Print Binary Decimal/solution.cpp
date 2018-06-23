class BinDecimal {
public:
    string printBin(double num) {
        // write code here
        int cnt = 1;
        string ans = "0.";
        while(num > 1e-7 && cnt < 32) {
            num *= 2;
            if(num >= 1) {
                ans.push_back('1');
                num -= 1;
            } else {
                ans.push_back('0');
            }
            cnt++;
        }
        if(cnt == 32) {
            return "Error";
        }
        return ans;
    }
};
