class Solution {
public:
    bool isEmail(const string& S) {
        return S.find('@') != std::string::npos;
    }
    string convertEmail(const string& S) {
        int at_idx = S.find('@');
        string res = "";
        res.push_back(S[0]);
        for (int i = 0; i < 5; i++)
            res.push_back('*');
        for (int i = at_idx - 1; i < S.length(); i++)
            res.push_back(S[i]);
        for (int i = 0; i < res.length(); i++) {
            if (res[i] >= 'A' && res[i] <= 'Z') {
                res[i] = res[i] - 'A' + 'a';
            }
        }
        return res;
    }
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    int countDigits(const string& S) {
        int digits = 0;
        for (auto c : S) {
            if (isDigit(c)) {
                digits++;
            }
        }
        return digits;
    }
    string convertPhoneNumber(const string& S) {
        int digits = countDigits(S);
        string res = "";

        bool hasCountryCode = digits > 10 ? true : false;
        if (hasCountryCode) {
            res.push_back('+');
            for (int i = 10; i < digits; i++) {
                res.push_back('*');
            }
            res.push_back('-');
        }
        // Now, res should look like : +**-
        res.append("***-***-");
        // Finally, unmasked digits
        for (int i = 0; i < S.length(); i++) {
            if (isDigit(S[i])) {
                digits--;
                if (digits < 4)
                    res.push_back(S[i]); 
            }

        }
        return res;
    }
    string maskPII(string S) {
        if (isEmail(S)) {
            return convertEmail(S);
        } else {
            return convertPhoneNumber(S);
        }
    }
};
