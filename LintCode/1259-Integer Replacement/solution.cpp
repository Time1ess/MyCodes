class Solution {
public:
    /**
     * @param n: a positive integer 
     * @return: the minimum number of replacements
     */
    int integerReplacement(int n) {
        // Write your code here
        int cnt = 0;
        while(n != 1) {
            if((n & 1) == 0) {
                n >>= 1;
            } else if(n == 3 || ((n >> 1) & 1) == 0) {
                n--;
            } else {
                n++;
            }
            cnt++;
        }
        return cnt;
    }
};
