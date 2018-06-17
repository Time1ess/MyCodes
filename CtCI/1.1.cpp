class Different {
public:
    bool checkDifferent(string iniString) {
        // write code here
        int n = iniString.length();
        if(n >= 256)
            return false;
        vector<int> flag(4, 0);
        for(auto c: iniString) {
            if(flag[c/32] & (1 << c))
                return false;
            flag[c/32] |= 1 << c;
        }
        return true;
    }
};
