class ReverseEqual {
public:
    bool checkReverseEqual(string s1, string s2) {
        if(s1.length() != s2.length())
            return false;
        string ds1 = s1 + s1;
        return ds1.find(s2) != string::npos;
    }
};
