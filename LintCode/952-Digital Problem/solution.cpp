class Solution {
public:
    /**
     * @param n: the number n 
     * @return: the times n convert to 1
     */
    int digitConvert(int n) {
        // Write your code here 
        int cnt = 0;
        while(n != 1)
        {
            if((n & 0x1) == 0)
                n /= 2;
            else
                n = 3 * n + 1;
            cnt++;
        }
        return cnt;
    }
};
