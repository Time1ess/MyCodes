class Zipper {
public:
    int digitsLength(int x) {
        int ans = 0;
        while(x) {
            ans += 1;
            x /= 10;
        }
        return ans;
    }
    int compressionLength(const string& s) {
        int ans = 0;
        char lastChar = '\0';
        int lastCnt = 0;
        for(auto c: s) {
            if(c == lastChar)
                lastCnt++;
            else {
                lastChar = c;
                ans += digitsLength(lastCnt);
                lastCnt = 1;
            }
        }
        return ans + digitsLength(lastCnt);
    }
    string compression(const string& s) {
        int n = s.length();
        string ans = "";
        char lastChar = s[0];
        int lastCnt = 1;
        for(int i = 1; i < n; i++)
            if(s[i] == lastChar)
                lastCnt++;
            else {
                ans.push_back(lastChar);
                ans.append(to_string(lastCnt));
                lastChar = s[i];
                lastCnt = 1;
            }
        ans.push_back(lastChar);
        ans.append(to_string(lastCnt));
        return ans;
    }
    string zipString(string iniString) {
        // write code here
        int n = iniString.length();
        if(n == 0 || compressionLength(iniString) >= n)
            return iniString;
        return compression(iniString);
    }
};
