class Solution {
public:
    /**
     * @param num: a string
     * @return: true if a number is strobogrammatic or false
     */
    bool isStrobogrammatic(string &num) {
        int n = num.length();
        int i = 0, j = n - 1;
        while(i <= j) {
            if(i == j)
                return num[i] == '1' || num[i] == '8' || num[i] == '0';
            else if((num[i] == '6' && num[j] == '9')
                    ||(num[i] == '9' && num[j] == '6')
                    ||(num[i] == '8' && num[j] == '8')
                    ||(num[i] == '1' && num[j] == '1')
                    ||(num[i] == '0' && num[j] == '0')) {
                i++, j--;
                continue;
            }
            return false;
        }
        return true;
    }
};
