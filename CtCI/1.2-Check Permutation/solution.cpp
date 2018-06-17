class Reverse {
public:
    string reverseString(string iniString) {
        // write code here
        int n = iniString.length();
        int i = 0, j = n - 1;
        while(i < j)
            swap(iniString[i++], iniString[j--]);
        return iniString;
    }
};
