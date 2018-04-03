class Solution {
public:
    /*
     * @param str: A string
     * @return: a boolean
     */
    bool isUnique(string &str) {
        // write your code here
        bool chars[256] = {false};
        for(auto c: str)
        {
            if(chars[c] == true)
                return false;
            chars[c] = true;
        }
        return true;
    }
};
