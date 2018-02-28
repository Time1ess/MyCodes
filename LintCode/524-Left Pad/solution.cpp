class StringUtils {
public:
    /*
     * @param originalStr: the string we want to append to
     * @param size: the target length of the string
     * @param padChar: the character to pad to the left side of the string
     * @return: A string
     */
    string leftPad(string &originalStr, int size, char padChar=' ') {
        // write your code here
        int str_len = originalStr.length();
        if(str_len >= size)
        {
            string ans = originalStr;
            return ans;
        }
        size -= str_len;
        string ans = "";
        ans.append(size, padChar);
        ans += originalStr;
        return ans;
    }
};
